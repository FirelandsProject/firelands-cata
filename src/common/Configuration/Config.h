/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU Affero General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "Define.h"
#include <string>
#include <vector>

class FC_COMMON_API ConfigMgr
{
    ConfigMgr() = default;
    ConfigMgr(ConfigMgr const&) = delete;
    ConfigMgr& operator=(ConfigMgr const&) = delete;
    ~ConfigMgr() = default;

  public:
    void Configure(std::string const& initFileName, std::vector<std::string> args, std::string_view modulesConfigList = {});
    // Load Authserver and Worldserver configs
    bool LoadConfigsCore(bool isReload = false);
    // Load Custom Modules Configs
    bool LoadConfigsModules(bool isReload = false, bool needsToPrintInfo = true);

    static ConfigMgr* instance();

    bool Reload(std::string& error);
    std::string const GetConfigPath();

    std::string GetStringDefault(std::string const& name, const std::string& def) const;
    bool GetBoolDefault(std::string const& name, bool def) const;
    int GetIntDefault(std::string const& name, int def) const;
    float GetFloatDefault(std::string const& name, float def) const;

    std::string const& GetFilename();
    std::vector<std::string> const& GetArguments() const;
    std::vector<std::string> GetKeysByString(std::string const& name);

  private:
    /// Method used only for loading main configuration files (authserver.conf and worldserver.conf)
    bool LoadInitial(std::string const& file, bool isReload = false);
    bool LoadAdditionalFile(std::string file, bool isOptional = false, bool isReload = false);

    template <class T> T GetValueDefault(std::string const& name, T def) const;

    std::vector<std::string> _moduleConfigFiles;
};

class ConfigException : public std::length_error
{
  public:
    explicit ConfigException(std::string const& message) : std::length_error(message) {}
};

#define sConfigMgr ConfigMgr::instance()

#endif
