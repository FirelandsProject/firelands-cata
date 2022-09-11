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

#include "ScriptPCH.h"
#include "Unit.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"
#include "GridNotifiers.h"


enum FrozenMountaineer
{
    DATA_SET_ICE_BROKEN      = 1,
    EVENT_RUN_AWAY           = 1,
    SAY_MONSTEREMOTE         = 0,
    SPELL_SUMMON_FROZEN_TOMB = 77906,
    SPELL_FREEZE_ANIM        = 77910
};

/*######
# npc_frozen_mountaineer
######*/

class npc_frozen_mountaineer : public CreatureScript
{
public:
    npc_frozen_mountaineer() : CreatureScript("npc_frozen_mountaineer") { }

    struct npc_frozen_mountaineerAI : public ScriptedAI
    {
        npc_frozen_mountaineerAI(Creature* creature) : ScriptedAI(creature), _dataOneSet(false) { }

        void Reset() override
        {
            _events.Reset();
            DoCastSelf(SPELL_SUMMON_FROZEN_TOMB, true);
            DoCastSelf(SPELL_FREEZE_ANIM, true);
        }

        void SetData(uint32 /*type*/, uint32 data) override
        {
            if (data == DATA_SET_ICE_BROKEN && !_dataOneSet)
            {
                me->RemoveAllAuras();
                Talk(SAY_MONSTEREMOTE);
                _dataOneSet = true;
                _events.ScheduleEvent(EVENT_RUN_AWAY, Seconds(3));
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (!_dataOneSet)
                return;

            _events.Update(diff);

            if (_events.ExecuteEvent() == EVENT_RUN_AWAY)
            {
                me->GetMotionMaster()->MovePoint(0, me->GetPositionX() + (std::cos(me->GetOrientation()) * 15.0f), me->GetPositionY() + (std::sin(me->GetOrientation()) * 15.0f), me->GetPositionZ());
                me->DespawnOrUnsummon(Seconds(2));
            }
        }
    private:
        EventMap _events;
        bool _dataOneSet;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_frozen_mountaineerAI(creature);
    }
};

/*######
## npc_sanitron500
######*/

/*
*  @Npc   : Sanitron 500 (46185)
*  @Quest : Decontamination (27635)
*  @Descr : Board the Sanitron 500 to begin the decontamination process.
*/
enum eSanitron
{
    SPELL_CANNON_BURST = 86080,
    SPELL_DECONTAMINATE_STAGE_1 = 86075,
    SPELL_DECONTAMINATE_STAGE_2 = 86086,
    SPELL_IRRADIATE = 80653,

    SPELL_EXPLOSION = 30934,

    QUEST_DECONTAMINATION = 27635,

    NPC_DECONTAMINATION_BUNNY = 46165,
    NPC_CLEAN_CANNON = 46208,
    NPC_SAFE_TECHNICAN = 46230,
};

enum  eTexts
{
    SAY_SANITRON_01 = 46323,
    SAY_SANITRON_02 = 46342,
    SAY_SANITRON_03 = 46324,
    SAY_SANITRON_04 = 46325,
};

class npc_sanitron500 : public CreatureScript
{
public:
    npc_sanitron500() : CreatureScript("npc_sanitron500") {}

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        QuestStatus status = pPlayer->GetQuestStatus(QUEST_DECONTAMINATION);
        if (status == QUEST_STATUS_INCOMPLETE)
        {
            pPlayer->HandleEmoteCommand(0);
            Vehicle* vehicle = pCreature->GetVehicleKit();
            pPlayer->EnterVehicle(pCreature->ToUnit(), 0);
            pCreature->Say(SAY_SANITRON_01);
        }
        return true;
    }

    struct npc_sanitron500AI : public ScriptedAI
    {
        npc_sanitron500AI(Creature* pCreature) : ScriptedAI(pCreature), vehicle(pCreature->GetVehicleKit())
        {
            assert(vehicle);
        }

        Vehicle* vehicle;
        Unit* Technician;
        Creature::Unit* Bunny[4];
        Creature::Unit* Cannon[4];
        std::list<Unit*> targets;
        uint32 uiTimer;
        uint32 uiRespawnTimer;
        uint8 uiPhase;

        void Reset()
        {
            uiTimer = 0;
            uiRespawnTimer = 6000;
            uiPhase = 0;
        }

        Unit* unit(uint32 entry, uint32 range, bool alive)
        {
            if (Unit* unit = me->FindNearestCreature(entry, float(range), alive))
                if (Unit* unit2 = Unit::GetCreature(*me, unit->GetGUID()))
                    return unit2;
        }

        void GetTargets()
        {
            Firelands::AnyUnitInObjectRangeCheck u_check(me, 100.0f);
            Firelands::UnitListSearcher<Firelands::AnyUnitInObjectRangeCheck> searcher(me, targets, u_check);
            me->VisitNearbyObject(100.0f, searcher);
            if (!targets.empty())
                for (std::list<Unit*>::const_iterator iter = targets.begin(); iter != targets.end(); ++iter)
                {
                    if ((*iter)->GetTypeId() != TYPEID_PLAYER)
                    {
                        switch ((*iter)->GetEntry())
                        {
                        case 46230:
                            if ((*iter)->GetDistance2d(-5165.209961f, 713.809021f) <= 1)
                                Technician = (*iter);
                            break;
                        case 46165:
                            if ((*iter)->GetDistance2d(-5164.919922f, 723.890991f) <= 1)
                                Bunny[0] = (*iter);
                            if ((*iter)->GetDistance2d(-5182.560059f, 726.656982f) <= 1)
                                Bunny[1] = (*iter);
                            if ((*iter)->GetDistance2d(-5166.350098f, 706.336975f) <= 1)
                                Bunny[2] = (*iter);
                            if ((*iter)->GetDistance2d(-5184.040039f, 708.405029f) <= 1)
                                Bunny[3] = (*iter);
                            break;
                        case 46208:
                            if ((*iter)->GetDistance2d(-5164.209961f, 719.267029f) <= 1)
                                Cannon[0] = (*iter);
                            if ((*iter)->GetDistance2d(-5165.000000f, 709.453979f) <= 1)
                                Cannon[1] = (*iter);
                            if ((*iter)->GetDistance2d(-5183.830078f, 722.093994f) <= 1)
                                Cannon[2] = (*iter);
                            if ((*iter)->GetDistance2d(-5184.470215f, 712.554993f) <= 1)
                                Cannon[3] = (*iter);
                            break;
                        }
                    }
                }
        }

        void UpdateAI(const uint32 diff)
        {
            if (!vehicle->HasEmptySeat(0))
                if (uiTimer <= diff)
                {
                    switch (uiPhase)
                    {
                    case 0: me->GetMotionMaster()->MovePoint(1, -5173.34f, 730.11f, 294.25f);
                        GetTargets();
                        ++uiPhase;
                        uiTimer = 5500;
                        break;
                    case 1:
                        if (Bunny[0] && Bunny[1])
                        {
                            Bunny[0]->CastSpell(me, SPELL_DECONTAMINATE_STAGE_1, true);
                            Bunny[1]->CastSpell(me, SPELL_DECONTAMINATE_STAGE_1, true);
                        }
                        ++uiPhase;
                        uiTimer = 5000;
                        break;
                    case 2:
                        if (Cannon[0] && Cannon[1] && Cannon[2] && Cannon[3])
                        {
                            me->GetMotionMaster()->MovePoint(2, -5173.72f, 725.7f, 294.03f);
                            Cannon[0]->CastSpell(me, SPELL_CANNON_BURST, true);
                            Cannon[1]->CastSpell(me, SPELL_CANNON_BURST, true);
                            Cannon[2]->CastSpell(me, SPELL_CANNON_BURST, true);
                            Cannon[3]->CastSpell(me, SPELL_CANNON_BURST, true);
                        }
                        ++uiPhase;
                        uiTimer = 2000;
                        break;
                    case 3:
                        if (Technician)
                            me->GetMotionMaster()->MovePoint(3, -5174.57f, 716.45f, 289.53f);
                        Technician->Say(SAY_SANITRON_02);
                        ++uiPhase;
                        uiTimer = 8000;
                        break;
                    case 4:
                        if (Bunny[2] && Bunny[3])
                        {
                            me->GetMotionMaster()->MovePoint(4, -5175.04f, 707.2f, 294.4f);
                            Bunny[2]->CastSpell(me, SPELL_DECONTAMINATE_STAGE_2, true);
                            Bunny[3]->CastSpell(me, SPELL_DECONTAMINATE_STAGE_2, true);
                        }
                        ++uiPhase;
                        uiTimer = 1000;
                        break;
                    case 5:
                        if (vehicle->GetPassenger(0))
                            if (Player* player = vehicle->GetPassenger(0)->ToPlayer())
                                player->CompleteQuest(QUEST_DECONTAMINATION);
                        me->Say(SAY_SANITRON_03);
                        me->GetMotionMaster()->MovePoint(5, -5175.61f, 700.38f, 290.89f);
                        ++uiPhase;
                        uiTimer = 3000;
                        break;
                    case 6:
                        me->Say(SAY_SANITRON_04);
                        me->CastSpell(me, SPELL_EXPLOSION);
                        ++uiPhase;
                        uiTimer = 1000;
                        break;
                    case 7:
                        me->SetCanFly(false);
                        vehicle->GetPassenger(0)->RemoveAurasDueToSpell(SPELL_IRRADIATE);
                        vehicle->RemoveAllPassengers();
                        me->setDeathState(JUST_DIED);
                        ++uiPhase;
                        uiTimer = 0;
                        break;
                    }
                }
                else uiTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_sanitron500AI(pCreature);
    }
};
void AddSC_dun_morogh()
{
    new npc_frozen_mountaineer();
    new npc_sanitron500();
}
