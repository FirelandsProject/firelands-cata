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

#ifndef FIRELANDS_GUARDAI_H
#define FIRELANDS_GUARDAI_H

#include "ScriptedCreature.h"

class Creature;

class FC_GAME_API GuardAI : public ScriptedAI
{
    public:
        explicit GuardAI(Creature* creature);

        static int32 Permissible(Creature const* creature);
        void UpdateAI(uint32 diff) override;
        bool CanSeeAlways(WorldObject const* obj) override;

        void EnterEvadeMode(EvadeReason /*why*/) override;
        void JustDied(Unit* killer) override;
};
#endif
