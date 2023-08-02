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

#include "Config.h"
#include "Log.h"
#include "StringConvert.h"
#include "Util.h"
#include <algorithm>
#include <fstream>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace
{
std::string _filename;
std::vector<std::string> _additionalFiles;
std::vector<std::string> _args;
std::unordered_map<std::string, std::string> _config;
std::mutex _configLock;

// Validate if Configuration is for worldserver or authserver
bool IsCoreConfig(std::string_view fileName)
{
    size_t foundAuth = fileName.find("authserver.conf");
    size_t foundWorld = fileName.find("worldserver.conf");

    return foundAuth != std::string_view::npos || foundWorld != std::string_view::npos;
}

// Check logging system configs like Appender.* and Logger.*
bool IsLoggingSystemOptions(std::string_view optionName)
{
    size_t foundAppender = optionName.find("Appender.");
    size_t foundLogger = optionName.find("Logger.");

    return foundAppender != std::string_view::npos || foundLogger != std::string_view::npos;
}

void AddKey(std::string const& optionName, std::string const& optionKey, std::string_view fileName, bool isOptional,
    [[maybe_unused]] bool isReload)
{
    auto const& itr = _config.find(optionName);

    // Check old option
    if (isOptional && itr == _config.end())
    {
        if (!IsLoggingSystemOptions(optionName) && !isReload)
        {
            std::string fname(fileName);
            LOG_ERROR(fname, "> Config::LoadFile: Found incorrect option '%s' in config file '%s'. Skip", optionName.c_str(),
                fname.c_str());
            return;
        }
    }

    // Check exit option
    if (itr != _config.end())
    {
        _config.erase(optionName);
    }

    _config.emplace(optionName, optionKey);
}

bool LoadFile(std::string const& file, bool isOptional, bool isReload)
{
    try
    {
        std::ifstream in(file);

        if (in.fail())
        {
            if (isOptional)
            {
                return false;
            }

            throw ConfigException(Firelands::StringFormat(
                "Config::LoadFile: Failed open %sfile '%s'", isOptional ? "optional " : "", file.c_str()));
        }

        uint32 count = 0;
        uint32 lineNumber = 0;
        std::unordered_map<std::string /*name*/, std::string /*value*/> fileConfigs;

        auto IsDuplicateOption = [&](std::string const& confOption)
        {
            auto const& itr = fileConfigs.find(confOption);
            if (itr != fileConfigs.end())
            {
                LOG_ERROR(
                    file, "> Config::LoadFile: Dublicate key name '%s' in config file '%s'", confOption.c_str(), file.c_str());
                return true;
            }

            return false;
        };

        while (in.good())
        {
            lineNumber++;
            std::string line;
            std::getline(in, line);

            // read line error
            if (!in.good() && !in.eof())
            {
                throw ConfigException(Firelands::StringFormat(
                    "> Config::LoadFile: Failure to read line number %u in file '%s'", lineNumber, file.c_str()));
            }

            line = Firelands::String::Trim(line, in.getloc());

            if (line.empty())
            {
                continue;
            }

            // comments
            if (line[0] == '#' || line[0] == '[')
            {
                continue;
            }

            size_t found = line.find_first_of('#');
            if (found != std::string::npos)
            {
                line = line.substr(0, found);
            }

            auto const equal_pos = line.find('=');

            if (equal_pos == std::string::npos || equal_pos == line.length())
            {
                LOG_ERROR(file, "> Config::LoadFile: Failure to read line number %u in file '%s'. Skip this line", lineNumber,
                    file.c_str());
                continue;
            }

            auto entry = Firelands::String::Trim(line.substr(0, equal_pos), in.getloc());
            auto value = Firelands::String::Trim(line.substr(equal_pos + 1, std::string::npos), in.getloc());

            value.erase(std::remove(value.begin(), value.end(), '"'), value.end());

            // Skip if 2+ same options in one config file
            if (IsDuplicateOption(entry))
            {
                continue;
            }

            // Add to temp container
            fileConfigs.emplace(entry, value);
            count++;
        }

        // No lines read
        if (!count)
        {
            if (isOptional)
            {
                // No display erorr if file optional
                return false;
            }

            throw ConfigException(Firelands::StringFormat("Config::LoadFile: Empty file '%s'", file.c_str()));
        }

        // Add correct keys if file load without errors
        for (auto const& [entry, key] : fileConfigs)
        {
            AddKey(entry, key, file, isOptional, isReload);
        }

        return true;
    }
    catch (const std::exception e)
    {
        LOG_ERROR(file, "%s", e.what());
        return false;
    }
}
} // namespace

void Configure(std::string const& initFileName, std::vector<std::string> args, std::string_view modulesConfigList)
{
    _filename = initFileName;
    _args = std::move(args);

    if (!modulesConfigList.empty())
    {
        std::string modulesConfigListStr(modulesConfigList);
        Tokenizer modulesConfig(modulesConfigListStr, ',');

        for (auto const& mod : modulesConfig)
        {
            _additionalFiles.emplace_back(mod);
        }
    }
}
bool ConfigMgr::LoadInitial(std::string const& file, bool isReload)
{
    std::lock_guard<std::mutex> lock(_configLock);
    _config.clear();
    return LoadFile(file, false, isReload);
}

std::string const ConfigMgr::GetConfigPath()
{
    std::lock_guard<std::mutex> lock(_configLock);

#if FC_PLATFORM == FC_PLATFORM_WINDOWS
    return "configs/";
#else
    return std::string(_CONF_DIR) + "/";
#endif
}

bool ConfigMgr::LoadConfigsCore(bool isReload)
{
    if (!LoadInitial(_filename, isReload))
    {
        return false;
    }

    return true;
}

bool ConfigMgr::LoadConfigsModules(bool isReload, bool needsToPrintInfo)
{
    if (_additionalFiles.empty())
    {
        // Returns True when no additional Files to load.
        return true;
    }

    if (needsToPrintInfo)
    {
        LOG_INFO("server.loading", "Loading Mods config");
    }

    std::string const& modsConfigPath = GetConfigPath() + "mods/";
    bool existsDefaultConfig = true;

    for (auto const& distFileName : _additionalFiles)
    {
        std::string defaultFileName = distFileName;
        if (defaultFileName.empty())
        {
            defaultFileName.erase(defaultFileName.end() - 5, defaultFileName.end());
        }

        existsDefaultConfig = LoadAdditionalFile(defaultFileName, false, isReload);

        if (existsDefaultConfig)
        {
            _moduleConfigFiles.emplace_back(defaultFileName);
        }

        if (needsToPrintInfo)
        {
            if (!_moduleConfigFiles.empty())
            {
                LOG_INFO("server.loading", "Using modules configuration:");

                for (auto const& itr : _moduleConfigFiles)
                {
                    LOG_INFO("server.loading", "> %s", itr.c_str());
                }
            }
            else
            {
                LOG_INFO("server.loading", "> Not found modules config files");
            }
        }
    }

    if (needsToPrintInfo)
    {
        LOG_INFO("server.loading", " ");
    }

    return true;
}

bool LoadAdditionalFile(std::string file, bool isOptional, bool isReload)
{
    std::lock_guard<std::mutex> lock(_configLock);
    return LoadFile(file, isOptional, isReload);
}

ConfigMgr* ConfigMgr::instance()
{
    static ConfigMgr instance;
    return &instance;
}

bool ConfigMgr::Reload(std::string& error)
{
    if (!LoadConfigsCore(true))
    {
        return false;
    }

    return LoadConfigsModules(true, false);
}

template <class T> T ConfigMgr::GetValueDefault(std::string const& name, T def) const
{
    auto const& itr = _config.find(name);
    if (itr == _config.end())
    {
        LOG_ERROR("server.loading", "> Config: Missing property %s in config file %s, add \"%s = %s\" to this file.",
            name.c_str(), _filename.c_str(), name.c_str(), Firelands::ToString(def).c_str());

        return def;
    }

    auto value = Firelands::StringTo<T>(itr->second);
    if (!value)
    {
        LOG_ERROR("server.loading", "> Config: Bad value defined for name '%s', going to use '%s' instead", name.c_str(),
            Firelands::ToString(def).c_str());

        return def;
    }

    return *value;
}

template <> std::string ConfigMgr::GetValueDefault<std::string>(std::string const& name, std::string def) const
{
    auto const& itr = _config.find(name);
    if (itr == _config.end())
    {
        LOG_ERROR("server.loading", "> Config: Missing property %s in config file %s, add \"%s = %s\" to this file.",
            name.c_str(), _filename.c_str(), name.c_str(), def.c_str());

        return def;
    }

    return itr->second;
}

std::string ConfigMgr::GetStringDefault(std::string const& name, const std::string& def) const
{
    std::string val = GetValueDefault(name, def);
    val.erase(std::remove(val.begin(), val.end(), '"'), val.end());
    return val;
}

bool ConfigMgr::GetBoolDefault(std::string const& name, bool def) const
{
    std::string val = GetValueDefault(name, std::string(def ? "1" : "0"));
    val.erase(std::remove(val.begin(), val.end(), '"'), val.end());
    return StringToBool(val);
}

int ConfigMgr::GetIntDefault(std::string const& name, int def) const { return GetValueDefault(name, def); }

float ConfigMgr::GetFloatDefault(std::string const& name, float def) const { return GetValueDefault(name, def); }

std::string const& ConfigMgr::GetFilename()
{
    std::lock_guard<std::mutex> lock(_configLock);
    return _filename;
}

std::vector<std::string> const& ConfigMgr::GetArguments() const { return _args; }

std::vector<std::string> ConfigMgr::GetKeysByString(std::string const& name)
{
    std::lock_guard<std::mutex> lock(_configLock);

    std::vector<std::string> keys;

    for (auto const& [optionName, key] : _config)
    {
        if (!optionName.compare(0, name.length(), name))
        {
            keys.emplace_back(optionName);
        }
    }

    return keys;
}
