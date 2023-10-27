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

#include "WorldSession.h"
#include "Common.h"
#include "DBCStores.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "Pet.h"
#include "Player.h"
#include "SpellMgr.h"
#include "WorldPacket.h"

enum Professions
{
    S_TRANSMUTE = 28672,
    S_ELIXIR = 28677,
    S_POTION = 28675,
    S_GOBLIN = 20222,
    S_GNOMISH = 20219,
};

enum Specializations
{
    SPEC_GNOMISH = 0,
    SPEC_GOBLIN = 1,
    SPEC_ELIXIR = 2,
    SPEC_POTION = 3,
    SPEC_TRANSMUTATION = 4,
};

void WorldSession::HandleLearnTalentOpcode(WorldPacket& recvData)
{
    uint32 talentId, requestedRank;
    recvData >> talentId >> requestedRank;

    if (_player->LearnTalent(talentId, requestedRank))
        _player->SendTalentsInfoData(false);
}

void WorldSession::HandleLearnPreviewTalents(WorldPacket& recvPacket)
{
    LOG_DEBUG("network", "CMSG_LEARN_PREVIEW_TALENTS");

    int32 tabPage;
    uint32 talentsCount;
    recvPacket >> tabPage;    // talent tree

    // prevent cheating (selecting new tree with points already in another)
    if (tabPage >= 0)   // -1 if player already has specialization
    {
        if (TalentTabEntry const* talentTabEntry = sTalentTabStore.LookupEntry(_player->GetPrimaryTalentTree(_player->GetActiveSpec())))
        {
            if (talentTabEntry->OrderIndex != uint32(tabPage))
            {
                recvPacket.rfinish();
                return;
            }
        }
    }

    recvPacket >> talentsCount;

    uint32 talentId, talentRank;

    // Client has max 21 talents for tree for 3 trees, rounded up : 70
    uint32 const MaxTalentsCount = 70;

    for (uint32 i = 0; i < talentsCount && i < MaxTalentsCount; ++i)
    {
        recvPacket >> talentId >> talentRank;

        if (!_player->LearnTalent(talentId, talentRank))
        {
            recvPacket.rfinish();
            break;
        }
    }

    _player->SendTalentsInfoData(false);

    recvPacket.rfinish();
}

void WorldSession::HandleTalentWipeConfirmOpcode(WorldPacket& recvData)
{
    LOG_DEBUG("network", "MSG_TALENT_WIPE_CONFIRM");
    ObjectGuid guid;
    recvData >> guid;

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_TRAINER);
    if (!unit)
    {
        LOG_DEBUG("network", "WORLD: HandleTalentWipeConfirmOpcode - %s not found or you can't interact with him.", guid.ToString().c_str());
        return;
    }

    if (!unit->CanResetTalents(_player))
        return;

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    if (!_player->ResetTalents())
    {
        WorldPacket data(MSG_TALENT_WIPE_CONFIRM, 8+4);    //you have not any talent
        data << uint64(0);
        data << uint32(0);
        SendPacket(&data);
        return;
    }

    _player->SendTalentsInfoData(false);
    unit->CastSpell(_player, 14867, true);                  //spell: "Untalent Visual Effect"
}

void WorldSession::HandleUnlearnSkillOpcode(WorldPacket& recvData)
{
    uint32 skillId;
    recvData >> skillId;

    SkillRaceClassInfoEntry const* rcEntry = sDBCManager.GetSkillRaceClassInfo(skillId, GetPlayer()->getRace(), GetPlayer()->getClass());
    if (!rcEntry || !(rcEntry->Flags & SKILL_FLAG_UNLEARNABLE))
        return;

    GetPlayer()->SetSkill(skillId, 0, 0, 0);
}

void WorldSession::HandleUnlearnSpecializationOpcode(WorldPacket& recvData)
{
    uint32 specialization = 0;
    uint32 spellId = 0;
    recvData >> specialization;

    switch (specialization)
    {
    case SPEC_GNOMISH:
        spellId = S_GNOMISH;
        break;
    case SPEC_GOBLIN:
        spellId = S_GOBLIN;
        break;
    case SPEC_ELIXIR:
        spellId = S_ELIXIR;
        break;
    case SPEC_POTION:
        spellId = S_POTION;
        break;
    case SPEC_TRANSMUTATION:
        spellId = S_TRANSMUTE;
        break;
    default:
        return;
    }

    GetPlayer()->RemoveSpell(spellId, false, false);
    GetPlayer()->RemoveRewardedSpecializationQuest(spellId);
}

void WorldSession::HandleCompletedArtifactsOpcode(WorldPacket& recv_data)
{
    uint32 skillId;
    recv_data >> skillId;

    WorldPacket data(SMSG_COMPLETED_ARTIFACTS, 4 + 12 * 1);
    data << uint32(1); // Number of artifact completed
    // FOR
    data << uint32(349);                // ID
    data << uint32(uint32(time(NULL))); // Time
    data << uint32(10);                 // Count
    // END FOR
    SendPacket(&data);
}
