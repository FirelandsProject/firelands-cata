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

#include "ScriptMgr.h"
#include "BattlefieldTB.h"
#include "DBCStores.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "SpellScript.h"

enum TBSpiritGuide
{
    SPELL_CHANNEL_SPIRIT_HEAL = 22011,

    GOSSIP_OPTION_ID_SLAGWORKS = 0,
    GOSSIP_OPTION_ID_IRONCLAD_GARRISON = 1,
    GOSSIP_OPTION_ID_WARDENS_VIGIL = 2,
    GOSSIP_OPTION_ID_EAST_SPIRE = 3,
    GOSSIP_OPTION_ID_WEST_SPIRE = 4,
    GOSSIP_OPTION_ID_SOUTH_SPIRE = 5,
};

class npc_tb_spirit_guide : public CreatureScript
{
    public:
        npc_tb_spirit_guide() : CreatureScript("npc_tb_spirit_guide") { }

        struct npc_tb_spirit_guideAI : public ScriptedAI
        {
            npc_tb_spirit_guideAI(Creature* creature) : ScriptedAI(creature) { }

            void UpdateAI(uint32 /*diff*/) override
            {
                if (!me->HasUnitState(UNIT_STATE_CASTING))
                    DoCast(me, SPELL_CHANNEL_SPIRIT_HEAL);
            }

            bool GossipSelect(Player* player, uint32 /*menuId*/, uint32 gossipListId) override
            {
                CloseGossipMenuFor(player);

                uint32 areaId = 0;
                switch (gossipListId)
                {
                    case GOSSIP_OPTION_ID_SLAGWORKS:
                        areaId = TB_GY_SLAGWORKS;
                        break;
                    case GOSSIP_OPTION_ID_IRONCLAD_GARRISON:
                        areaId = TB_GY_IRONCLAD_GARRISON;
                        break;
                    case GOSSIP_OPTION_ID_WARDENS_VIGIL:
                        areaId = TB_GY_WARDENS_VIGIL;
                        break;
                    case GOSSIP_OPTION_ID_EAST_SPIRE:
                        areaId = TB_GY_EAST_SPIRE;
                        break;
                    case GOSSIP_OPTION_ID_WEST_SPIRE:
                        areaId = TB_GY_WEST_SPIRE;
                        break;
                    case GOSSIP_OPTION_ID_SOUTH_SPIRE:
                        areaId = TB_GY_SOUTH_SPIRE;
                        break;
                    default:
                        return true;
                }

                if (WorldSafeLocsEntry const* safeLoc = sWorldSafeLocsStore.LookupEntry(areaId))
                    player->TeleportTo(safeLoc->Continent, safeLoc->Loc.X, safeLoc->Loc.Y, safeLoc->Loc.Z, 0);
                return true;
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new npc_tb_spirit_guideAI(creature);
        }
};

// 85123 - Siege Cannon - selects random target
class spell_siege_cannon : public SpellScriptLoader
{
public:
    spell_siege_cannon() : SpellScriptLoader("spell_siege_cannon") { }

    class spell_siege_cannon_SpellScript : public SpellScript
    {
        void SelectRandomTarget(std::list<WorldObject*>& targets)
        {
            if (targets.empty())
                return;

            WorldObject* target = Firelands::Containers::SelectRandomContainerElement(targets);
            targets.clear();
            targets.push_back(target);
        }

        void Register() override
        {
            OnObjectAreaTargetSelect.Register(&spell_siege_cannon_SpellScript::SelectRandomTarget, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_siege_cannon_SpellScript();
    }
};

enum MagnestsHowDoTheyWork
{
    SPELL_SCRAPS = 88440
};

// 88443 - Scrap Master Summon
class spell_tb_scrap_master_summon : public SpellScript
{
    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SCRAPS });
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        GetHitUnit()->CastSpell(nullptr, SPELL_SCRAPS);
    }

    void Register() override
    {
        OnEffectHitTarget.Register(&spell_tb_scrap_master_summon::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void AddSC_tol_barad()
{
    new npc_tb_spirit_guide();
    new spell_siege_cannon();
    RegisterSpellScript(spell_tb_scrap_master_summon);
}
