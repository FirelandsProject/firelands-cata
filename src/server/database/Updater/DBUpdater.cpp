/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "DBUpdater.h"
#include "BuiltInConfig.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "DatabaseLoader.h"
#include "GitRevision.h"
#include "Log.h"
#include "QueryResult.h"
#include "StartProcess.h"
#include "UpdateFetcher.h"
#include <boost/filesystem/operations.hpp>
#include <fstream>
#include <iostream>

std::string DBUpdaterUtil::GetCorrectedMySQLExecutable()
{
    if (!corrected_path().empty())
        return corrected_path();
    else
        return BuiltInConfig::GetMySQLExecutable();
}

bool DBUpdaterUtil::CheckExecutable()
{
    boost::filesystem::path exe(GetCorrectedMySQLExecutable());
    if (!is_regular_file(exe))
    {
        exe = Firelands::SearchExecutableInPath("mysql");
        if (!exe.empty() && is_regular_file(exe))
        {
            // Correct the path to the cli
            corrected_path() = absolute(exe).generic_string();
            return true;
        }

        LOG_FATAL("sql.updates", "Didn't find any executable MySQL binary at \'%s\' or in path, correct the path in the *.conf (\"MySQLExecutable\").",
                  absolute(exe).generic_string().c_str());

        return false;
    }
    return true;
}

std::string &DBUpdaterUtil::corrected_path()
{
    static std::string path;
    return path;
}

// Auth Database
template <>
std::string DBUpdater<LoginDatabaseConnection>::GetConfigEntry()
{
    return "Updates.Auth";
}

template <>
std::string DBUpdater<LoginDatabaseConnection>::GetTableName()
{
    return "Auth";
}

template <>
std::string DBUpdater<LoginDatabaseConnection>::GetBaseDirectory()
{
    return BuiltInConfig::GetSourceDirectory() +
           "/data/sql/base/db_auth/";
}

template <>
bool DBUpdater<LoginDatabaseConnection>::IsEnabled(uint32 const updateMask)
{
    // This way silences warnings under msvc
    return (updateMask & DatabaseLoader::DATABASE_LOGIN) ? true : false;
}

// World Database
template <>
std::string DBUpdater<WorldDatabaseConnection>::GetConfigEntry()
{
    return "Updates.World";
}

template <>
std::string DBUpdater<WorldDatabaseConnection>::GetTableName()
{
    return "World";
}

template <>
std::string DBUpdater<WorldDatabaseConnection>::GetBaseDirectory()
{
    return BuiltInConfig::GetSourceDirectory() +
           "/data/sql/base/db_world/";
}

template <>
bool DBUpdater<WorldDatabaseConnection>::IsEnabled(uint32 const updateMask)
{
    // This way silences warnings under msvc
    return (updateMask & DatabaseLoader::DATABASE_WORLD) ? true : false;
}

template <>
BaseLocation DBUpdater<WorldDatabaseConnection>::GetBaseLocationType()
{
    return LOCATION_REPOSITORY;
}

// Character Database
template <>
std::string DBUpdater<CharacterDatabaseConnection>::GetConfigEntry()
{
    return "Updates.Character";
}

template <>
std::string DBUpdater<CharacterDatabaseConnection>::GetTableName()
{
    return "Character";
}

template <>
std::string DBUpdater<CharacterDatabaseConnection>::GetBaseDirectory()
{
    return BuiltInConfig::GetSourceDirectory() +
           "/data/sql/base/db_characters";
}

template <>
bool DBUpdater<CharacterDatabaseConnection>::IsEnabled(uint32 const updateMask)
{
    // This way silences warnings under msvc
    return (updateMask & DatabaseLoader::DATABASE_CHARACTER) ? true : false;
}

// Hotfix Database
template <>
std::string DBUpdater<HotfixDatabaseConnection>::GetConfigEntry()
{
    return "Updates.Hotfix";
}

template <>
std::string DBUpdater<HotfixDatabaseConnection>::GetTableName()
{
    return "Hotfixes";
}

template <>
std::string DBUpdater<HotfixDatabaseConnection>::GetBaseDirectory()
{
    return BuiltInConfig::GetSourceDirectory() +
           "/data/sql/base/db_hotfixes/";
}

template <>
bool DBUpdater<HotfixDatabaseConnection>::IsEnabled(uint32 const updateMask)
{
    // This way silences warnings under msvc
    return (updateMask & DatabaseLoader::DATABASE_HOTFIX) ? true : false;
}

template <>
BaseLocation DBUpdater<HotfixDatabaseConnection>::GetBaseLocationType()
{
    return LOCATION_REPOSITORY;
}

// All
template <class T>
BaseLocation DBUpdater<T>::GetBaseLocationType()
{
    return LOCATION_REPOSITORY;
}

template <class T>
bool DBUpdater<T>::Create(DatabaseWorkerPool<T> &pool)
{
    LOG_INFO("sql.updates", "Database \"%s\" does not exist, do you want to create it? [yes (default) / no]: ",
             pool.GetConnectionInfo()->database.c_str());

    std::string answer;
    std::getline(std::cin, answer);
    if (!answer.empty() && !(answer.substr(0, 1) == "y"))
        return false;

    LOG_INFO("sql.updates", "Creating database \"%s\"...", pool.GetConnectionInfo()->database.c_str());

    // Path of temp file
    static Path const temp("create_table.sql");

    // Create temporary query to use external MySQL CLi
    std::ofstream file(temp.generic_string());
    if (!file.is_open())
    {
        LOG_FATAL("sql.updates", "Failed to create temporary query file \"%s\"!", temp.generic_string().c_str());
        return false;
    }

    file << "CREATE DATABASE `" << pool.GetConnectionInfo()->database << "` DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci\n\n";

    file.close();

    try
    {
        DBUpdater<T>::ApplyFile(pool, pool.GetConnectionInfo()->host, pool.GetConnectionInfo()->user, pool.GetConnectionInfo()->password,
                                pool.GetConnectionInfo()->port_or_socket, "", temp);
    }
    catch (UpdateException &)
    {
        LOG_FATAL("sql.updates", "Failed to create database %s! Does the user (named in *.conf) have `CREATE` privileges on the MySQL server?", pool.GetConnectionInfo()->database.c_str());
        boost::filesystem::remove(temp);
        return false;
    }

    LOG_INFO("sql.updates", "Done.");
    boost::filesystem::remove(temp);
    return true;
}

template <class T>
bool DBUpdater<T>::Update(DatabaseWorkerPool<T> &pool)
{
    if (!DBUpdaterUtil::CheckExecutable())
        return false;

    LOG_INFO("sql.updates", "Updating %s database...", DBUpdater<T>::GetTableName().c_str());

    Path const sourceDirectory(BuiltInConfig::GetSourceDirectory());

    if (!is_directory(sourceDirectory))
    {
        LOG_ERROR("sql.updates", "DBUpdater: Given source directory %s does not exist, skipped!", sourceDirectory.generic_string().c_str());
        return false;
    }

    UpdateFetcher updateFetcher(
        sourceDirectory, [&](std::string const &query)
        { DBUpdater<T>::Apply(pool, query); },
        [&](Path const &file)
        { DBUpdater<T>::ApplyFile(pool, file); },
        [&](std::string const &query) -> QueryResult
        { return DBUpdater<T>::Retrieve(pool, query); });

    UpdateResult result;
    try
    {
        result = updateFetcher.Update(
            sConfigMgr->GetBoolDefault("Updates.Redundancy", true),
            sConfigMgr->GetBoolDefault("Updates.AllowRehash", true),
            sConfigMgr->GetBoolDefault("Updates.ArchivedRedundancy", false),
            sConfigMgr->GetIntDefault("Updates.CleanDeadRefMaxCount", 3));
    }
    catch (UpdateException &)
    {
        return false;
    }

    std::string const info = Firelands::StringFormat("Containing " SZFMTD " new and " SZFMTD " archived updates.",
                                                     result.recent, result.archived);

    if (!result.updated)
        LOG_INFO("sql.updates", ">> %s database is up-to-date! %s", DBUpdater<T>::GetTableName().c_str(), info.c_str());
    else
        LOG_INFO("sql.updates", ">> Applied " SZFMTD " %s. %s", result.updated, result.updated == 1 ? "query" : "queries", info.c_str());

    return true;
}

template <class T>
bool DBUpdater<T>::Populate(DatabaseWorkerPool<T> &pool)
{
    {
        QueryResult const result = Retrieve(pool, "SHOW TABLES");
        if (result && (result->GetRowCount() > 0))
            return true;
    }

    if (!DBUpdaterUtil::CheckExecutable())
        return false;

    LOG_INFO("sql.updates", "Database %s is empty, auto populating it...", DBUpdater<T>::GetTableName().c_str());

    std::string const pathDirectory = DBUpdater<T>::GetBaseDirectory();

    Path const base(pathDirectory);
    if (pathDirectory.empty())
    {
        LOG_INFO("sql.updates", ">> No base directory provided, skipped!");
        return true;
    }

    if (!boost::filesystem::is_directory(base))
    {
        switch (DBUpdater<T>::GetBaseLocationType())
        {
        case LOCATION_REPOSITORY:
        {
            LOG_ERROR("sql.updates", ">> Base file \"%s\" is missing, try to clone the source again.",
                      base.generic_string().c_str());

            break;
        }
        case LOCATION_DOWNLOAD:
        {
            std::string const filename = base.filename().generic_string();
            std::string const workdir = boost::filesystem::current_path().generic_string();
            LOG_ERROR("sql.updates", ">> File \"%s\" is missing, download it from \"https://github.com/FirelandsProject/firelands-cata/releases\""
                                     " uncompress it and place the file \"%s\" in the directory \"%s\".",
                      filename.c_str(), filename.c_str(), workdir.c_str());
            break;
        }
        }
        return false;
    }

    boost::filesystem::directory_iterator dirIt;
    uint32 filesCount = 0;
    for (boost::filesystem::directory_iterator it(base); it != dirIt; ++it)
    {
        if (it->path().extension() == ".sql")
        {
            filesCount++;
        }
    }

    if (!filesCount)
    {
        LOG_ERROR("sql.updates", ">> In directory \"%s\" not exist '*.sql' files", base.generic_string().c_str());
        return false;
    }

    for (boost::filesystem::directory_iterator it(base); it != dirIt; ++it)
    {
        if (it->path().extension() != ".sql")
        {
            continue;
        }

        LOG_INFO("sql.updates", ">> Applying \'%s\'...", it->path().filename().generic_string().c_str());
        try
        {
            ApplyFile(pool, it->path());
        }
        catch (UpdateException &)
        {
            return false;
        }
    }

    LOG_INFO("sql.updates", ">> Done!");
    LOG_INFO("sql.updates", " ");
    return true;
}

template <class T>
QueryResult DBUpdater<T>::Retrieve(DatabaseWorkerPool<T> &pool, std::string const &query)
{
    return pool.Query(query.c_str());
}

template <class T>
void DBUpdater<T>::Apply(DatabaseWorkerPool<T> &pool, std::string const &query)
{
    pool.DirectExecute(query.c_str());
}

template <class T>
void DBUpdater<T>::ApplyFile(DatabaseWorkerPool<T> &pool, Path const &path)
{
    DBUpdater<T>::ApplyFile(pool, pool.GetConnectionInfo()->host, pool.GetConnectionInfo()->user, pool.GetConnectionInfo()->password,
                            pool.GetConnectionInfo()->port_or_socket, pool.GetConnectionInfo()->database, path);
}

template <class T>
void DBUpdater<T>::ApplyFile(DatabaseWorkerPool<T> &pool, std::string const &host, std::string const &user,
                             std::string const &password, std::string const &port_or_socket, std::string const &database, Path const &path)
{
    std::vector<std::string> args;
    args.reserve(9);

    // CLI Client connection info
    args.emplace_back("-h" + host);
    args.emplace_back("-u" + user);

    if (!password.empty())
        args.emplace_back("-p" + password);

        // Check if we want to connect through ip or socket (Unix only)
#ifdef _WIN32

    if (host == ".")
        args.emplace_back("--protocol=PIPE");
    else
        args.emplace_back("-P" + port_or_socket);

#else

    if (!std::isdigit(port_or_socket[0]))
    {
        // We can't check if host == "." here, because it is named localhost if socket option is enabled
        args.emplace_back("-P0");
        args.emplace_back("--protocol=SOCKET");
        args.emplace_back("-S" + port_or_socket);
    }
    else
        // generic case
        args.emplace_back("-P" + port_or_socket);

#endif

    // Set the default charset to utf8
    args.emplace_back("--default-character-set=utf8");

    // Set max allowed packet to 1 GB
    args.emplace_back("--max-allowed-packet=1GB");

    // Excute SQL file
    args.emplace_back("-e");
    args.emplace_back(Firelands::StringFormat("BEGIN; SOURCE %s; COMMIT;", path.generic_string().c_str()));

    // Database
    if (!database.empty())
        args.emplace_back(database);

    // Invokes a mysql process which doesn't leak credentials to logs
    int const ret = Firelands::StartProcess(DBUpdaterUtil::GetCorrectedMySQLExecutable(), args,
        "sql.updates", "", true);

    if (ret != EXIT_SUCCESS)
    {
        LOG_FATAL("sql.updates", "Applying of file \'%s\' to database \'%s\' failed!"
                                 " If you are a user, pull the latest revision from the repository. If you are a developer, fix your sql query.",
                  path.generic_string().c_str(), pool.GetConnectionInfo()->database.c_str());

        throw UpdateException("update failed");
    }
}

template class FC_DATABASE_API DBUpdater<LoginDatabaseConnection>;
template class FC_DATABASE_API DBUpdater<WorldDatabaseConnection>;
template class FC_DATABASE_API DBUpdater<CharacterDatabaseConnection>;
template class FC_DATABASE_API DBUpdater<HotfixDatabaseConnection>;
