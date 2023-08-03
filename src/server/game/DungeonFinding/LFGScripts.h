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

#ifndef LFGScripts_h__
#define LFGScripts_h__

/*
 * Interaction between core and LFGScripts
 */

#include "Common.h"
#include "SharedDefines.h"
#include "ScriptMgr.h"

class Player;
class Group;

namespace lfg
{

class FC_GAME_API LFGPlayerScript : public PlayerScript
{
    public:
        LFGPlayerScript();

        // Player Hooks
        void OnLogout(Player* player) override;
        void OnLogin(Player* player, bool loginFirst) override;
        void OnMapChanged(Player* player) override;
};

class FC_GAME_API LFGGroupScript : public GroupScript
{
    public:
        LFGGroupScript();

        // Group Hooks
        void OnAddMember(Group* group, ObjectGuid guid) override;
        void OnRemoveMember(Group* group, ObjectGuid guid, RemoveMethod method, ObjectGuid kicker, char const* reason) override;
        void OnDisband(Group* group) override;
        void OnChangeLeader(Group* group, ObjectGuid newLeaderGuid, ObjectGuid oldLeaderGuid) override;
        void OnInviteMember(Group* group, ObjectGuid guid) override;
};

/*keep private*/ void AddSC_LFGScripts();

} // namespace lfg

#endif // LFGScripts_h__
