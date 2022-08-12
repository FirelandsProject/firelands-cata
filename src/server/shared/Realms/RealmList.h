/*
 * Copyright (C) 2022 Firelands <https://github.com/FirelandsProject/>
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
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

#ifndef RealmList_h__
#define RealmList_h__

#include <map>
#include <unordered_set>
#include <vector>

#include "Define.h"
#include "Realm.h"

namespace boost {
namespace system {
class error_code;
}
}  // namespace boost

namespace Firelands {
namespace Asio {
class IoContext;
class DeadlineTimer;
}  // namespace Asio
}  // namespace Firelands

/// Storage object for the list of realms on the server
class RealmList {
 public:
  typedef std::map<Battlenet::RealmHandle, Realm> RealmMap;

  static RealmList *Instance();

  ~RealmList();

  void Initialize(Firelands::Asio::IoContext &ioContext, uint32 updateInterval);
  void Close();

  RealmMap const &GetRealms() const { return _realms; }
  Realm const *GetRealm(Battlenet::RealmHandle const &id) const;

 private:
  RealmList();

  void UpdateRealms(boost::system::error_code const &error);
  void UpdateRealm(Battlenet::RealmHandle const &id, uint32 build,
                   std::string const &name, boost::asio::ip::address &&address,
                   boost::asio::ip::address &&localAddr,
                   boost::asio::ip::address &&localSubmask, uint16 port,
                   uint8 icon, RealmFlags flag, uint8 timezone,
                   AccountTypes allowedSecurityLevel, float population);

  RealmMap _realms;
  uint32 _updateInterval;
  std::unique_ptr<Firelands::Asio::DeadlineTimer> _updateTimer;
  std::unique_ptr<Firelands::Asio::Resolver> _resolver;
};

#define sRealmList RealmList::Instance()

#endif  // RealmList_h__
