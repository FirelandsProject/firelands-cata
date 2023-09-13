#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "SpellScript.h"
#include "SpellMgr.h"
#include "MoveSplineInit.h"
#include "MotionMaster.h"
#include "Cell.h"
#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "dragon_soul.h"
#include "SpellAuraEffects.h"
#include "InstanceScript.h"
#include "Vehicle.h"

// clang-format off
enum Dialogs
{
    TALK_EVENT_GROUP_ONE                = 0,
    TALK_EVENT_GROUP_ONE_2              = 1,
    TALK_EVENT_GROUP_TWO                = 2,
    TALK_EVENT_GROUP_TWO_2              = 3,
    TALK_AGGRO                          = 4,
    TALK_SUMMON_KOHCROM                 = 5,
    TALK_SUMMON_RESONATING_CRYSTAL      = 6,
    TALK_EARTHEN_VORTEX                 = 7,
    TALK_BLACK_BLOOD_OF_THE_EARTH       = 8,
    TALK_KILLING_A_PLAYER               = 9,
    TALK_DEATH                          = 10
};
// clang-format on

// clang-format off
enum MorchokSpells
{
    // Morchok
    SPELL_SIEGE_MISSILE                 = 107541,
    SPELL_CRUSH_ARMOR                   = 103687,
    SPELL_STOMP                         = 103414,
    SPELL_FURIOUS                       = 103846,
    SPELL_RESONATING_CRYSTAL_SUMMON     = 103640,
    SPELL_BLACK_BLOOD_OF_THE_EARTH      = 103851,
    SPELL_BLACK_BLOOD_GROUND_VISUAL     = 103180,
    SPELL_FALLING_FRAGMENT_PERIODIC     = 103176,
    SPELL_FALLING_FRAGMENT_MISSILE      = 103177,
    SPELL_EARTHEN_VORTEX                = 103821,
    SPELL_BERSERK                       = 64238,
    SPELL_SHARE_HEALTH                  = 109548,
    // crystal
    SPELL_RESONATING_CRYSTAL            = 103494,
    SPELL_TARGET_SELECTION              = 103528,
    SPELL_DANGER                        = 103534,
    SPELL_WARNING                       = 103536,
    SPELL_SAFE                          = 103541,
    SPELL_CRYSTAL_EXPLOSION             = 103545,

    // Earthen Vortex vehicle
    SPELL_EARTHEN_VORTEX_RIDE_VEHICLE   = 109615,
    SPELL_BURROW                        = 108246,

    // Heroic
    SPELL_SUMMON_KOHCROM                = 109017,
};

enum Events
{
    EVENT_STOMP                     = 1,
    EVENT_RESONATING_CRYSTAL        = 2,
    EVENT_EARTHEN_VOTEX             = 3,
    EVENT_BLACK_BLOOD_OF_THE_EARTH  = 4,
    EVENT_BLACK_BLOOD_ENDS          = 5,
    EVENT_FALLING_FRAGMENTS         = 6,
    EVENT_CRUSH_ARMOR               = 7,
    EVENT_BERSERK                   = 8,
    EVENT_REACT_AGGRESSIVE          = 9

};

enum Phases
{
    PHASE_ALL = 0,
    PHASE_ONE = 1,
    PHASE_TWO = 2
};

enum VehicleTargetHandling
{
    DATA_VEHICLE_TARGET    = 100,
    VEHICLE_TARGET_MORCHOK = 200,
    VEHICLE_TARGET_KOHCROM = 300
};

enum Actions
{
    ACTION_STOMP    = 1
};
// clang-format on

class VortexVisualEvent : public BasicEvent
{
  public:
    VortexVisualEvent(Creature* owner) : _owner(owner) {}

    bool Execute(uint64 execTime, uint32 /*diff*/)
    {
        _owner->CastSpell(_owner, SPELL_BLACK_BLOOD_GROUND_VISUAL, true);
        _owner->m_Events.AddEvent(this, execTime + EVENT_OFFSET);
        return false;
    }

  private:
    Creature* _owner;
    uint32 EVENT_OFFSET = 3500;
};

struct boss_morchok : public BossAI
{
    boss_morchok(Creature* creature) : BossAI(creature, DATA_MORCHOK), _kocromSummoned(false) {}

    void Reset() override
    {
        me->SetReactState(REACT_AGGRESSIVE);
        RemoveFragments(true);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DANGER);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WARNING);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SAFE);
        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        me->SetObjectScale(1.00f);
        currentVehicleTarget = VEHICLE_TARGET_MORCHOK;
        _Reset();
        if (instance->GetData(DATA_RAID_MODE) == RAID_MODE_LFR)
        {
            if (!me->HasAura(SPELL_PRESENCE_OF_THE_DRAGON_SOUL))
                me->CastSpell(me, SPELL_PRESENCE_OF_THE_DRAGON_SOUL, true);
            me->SetLootMode(LOOT_MODE_LFR);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        switch (summon->GetEntry())
        {
        case NPC_RESONATING_CRYSTAL:
            summon->CastSpell(summon, SPELL_RESONATING_CRYSTAL, true);
            break;
        case NPC_WORLD_TRIGGER_VISUAL:
            summon->CastSpell(summon, SPELL_BLACK_BLOOD_GROUND_VISUAL, true);
            summon->m_Events.AddEvent(new VortexVisualEvent(summon), summon->m_Events.CalculateTime(3500));
            break;
        case NPC_KOHCROM:
        {
            me->AttackStop();
            me->SetReactState(REACT_PASSIVE);
            summon->SetReactState(REACT_PASSIVE);
            Position kohcromDest(*me);
            Position morchokDest(*me);
            oldOrientation = morchokDest.GetOrientation();
            summon->SetMaxHealth(me->GetMaxHealth());
            summon->SetHealth(me->GetHealth());
            me->MovePosition(kohcromDest, 20.00f, -M_PI / 2);
            me->MovePosition(morchokDest, 20.00f, M_PI / 2);
            me->GetMotionMaster()->MoveJump(morchokDest, 20.00f, 10.00f);
            summon->GetMotionMaster()->MoveJump(kohcromDest, 20.00f, 10.00f);
        }
        break;
        default:
            break;
        }
        BossAI::JustSummoned(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_KOHCROM)
            instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, summon);

        BossAI::SummonedCreatureDespawn(summon);
    }

    void DamageTaken(Unit* attacker, uint32& damage) override
    {
        if (!me->HasAura(SPELL_FURIOUS) && me->HealthBelowPctDamaged(20, damage))
            DoCast(me, SPELL_FURIOUS, true);

        if (IsHeroic() && !_kocromSummoned && me->HealthBelowPctDamaged(90, damage))
        {
            _kocromSummoned = true;
            Talk(TALK_SUMMON_KOHCROM);
            uint32 stompTimer = events.GetNextEventTime(EVENT_STOMP) - events.GetTimer();
            uint32 crystalTimer = events.GetNextEventTime(EVENT_RESONATING_CRYSTAL) - events.GetTimer();

            if (stompTimer > crystalTimer)
            {
                events.RescheduleEvent(EVENT_RESONATING_CRYSTAL, 5500, 0, PHASE_ONE);
                events.RescheduleEvent(EVENT_STOMP, 12000, 0, PHASE_ONE);
            }
            else
            {
                events.RescheduleEvent(EVENT_RESONATING_CRYSTAL, 15000, 0, PHASE_ONE);
                events.RescheduleEvent(EVENT_STOMP, 6000, 0, PHASE_ONE);
            }

            DoCast(me, SPELL_SUMMON_KOHCROM, true);
        }

        if (IsHeroic())
        {
            if (Creature* kohcrom = me->FindNearestCreature(NPC_KOHCROM, 500.00f))
            {
                if (me->HealthBelowPct(2) && !kohcrom->HealthBelowPct(2))
                    damage = 0;
                else
                {
                    if (attacker != kohcrom)
                    {
                        damage /= 2;
                        Unit::DealDamage(me, kohcrom, damage);
                    }
                }
            }
        }

        me->SetObjectScale(std::max((me->GetHealthPct() / 100), 0.10f));
    }

    void JustEnteredCombat(Unit* victim) override
    {
        if (instance->GetData(DATA_RAID_MODE) == RAID_MODE_LFR)
            me->SetLootMode(LOOT_MODE_LFR);

        if (IsHeroic())
            me->LowerPlayerDamageReq(me->GetMaxHealth()); // group is splitted we need to remove the damage req because only 50% of the group can loot morchok

        firstPhase = true;
        crystalCount = 0;
        stompCount = 0;
        Talk(TALK_AGGRO);
        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        events.SetPhase(PHASE_ONE);
        if (!IsHeroic())
            events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(5000, 6000), 0, PHASE_ONE);

        events.ScheduleEvent(EVENT_STOMP, 12000, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, 19000, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_EARTHEN_VOTEX, 60000, 0, PHASE_ONE);
        events.ScheduleEvent(EVENT_BERSERK, 7 * IN_MILLISECONDS * MINUTE, 0, PHASE_ALL);
        BossAI::JustEnteredCombat(victim);
    }

    void JustDied(Unit* killer) override
    {
        RemoveFragments(true);
        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_DANGER);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_WARNING);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_SAFE);
        if (IsHeroic())
            instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, NPC_MORCHOK, 1, me);

        _JustDied();
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(TALK_KILLING_A_PLAYER);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == EFFECT_MOTION_TYPE && id == EVENT_JUMP)
        {
            me->SetFacingTo(oldOrientation);
            events.ScheduleEvent(EVENT_REACT_AGGRESSIVE, 2500);
        }
    }

    void RemoveFragments(bool fullReset)
    {
        std::list<GameObject*> fallingFragments;
        me->GetGameObjectListWithEntryInGrid(fallingFragments, GO_FALLING_FRAGMENT, 300.0f);
        for (auto itr = fallingFragments.begin(); itr != fallingFragments.end(); itr++)
        {
            if (GameObject* fragment = (*itr))
            {
                if (fragment->GetOwner() == me || fullReset)
                {
                    fragment->UseDoorOrButton();
                    fragment->Delete(2000);
                }
            }
        }
    }

    uint32 GetData(uint32 data) const override
    {
        if (data == DATA_VEHICLE_TARGET)
            return currentVehicleTarget;

        return events.GetNextEventTime(data) - events.GetTimer();
    }

    void SetData(uint32 data, uint32 value) override
    {
        if (data == DATA_VEHICLE_TARGET)
            currentVehicleTarget = value;
    }

    void UpdateAI(uint32 const diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventid = events.ExecuteEvent())
        {
            switch (eventid)
            {
            case EVENT_STOMP:
                DoCast(me, SPELL_STOMP);
                if (++stompCount < (firstPhase ? 3 : 4))
                {
                    if (IsHeroic())
                        if (Creature* kohcrom = me->FindNearestCreature(NPC_KOHCROM, 500.00f))
                            kohcrom->AI()->DoAction(ACTION_STOMP);
                    events.ScheduleEvent(EVENT_STOMP, urand(12000, 14000), 0, PHASE_ONE);
                }
                break;
            case EVENT_RESONATING_CRYSTAL:
            {
                Talk(TALK_SUMMON_RESONATING_CRYSTAL);
                float angle = frand(0.0f, 2.0f * M_PI);
                float dist = frand(25.0f, 35.0f);
                float tempAngle = me->NormalizeOrientation(angle);
                Position pos(*me);
                me->MovePosition(pos, dist, tempAngle);
                me->CastSpell(pos, SPELL_RESONATING_CRYSTAL_SUMMON, true);

                if (++crystalCount < (firstPhase ? 2 : 3))
                    events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, 14000, 0, PHASE_ONE);

                break;
            }
            case EVENT_EARTHEN_VOTEX:
                currentVehicleTarget = VEHICLE_TARGET_MORCHOK;
                Talk(TALK_EARTHEN_VORTEX);
                DoCast(me, SPELL_EARTHEN_VORTEX);
                events.SetPhase(PHASE_TWO);
                events.ScheduleEvent(EVENT_FALLING_FRAGMENTS, 100, 0, PHASE_TWO);
                firstPhase = false;
                crystalCount = 0;
                stompCount = 0;
                break;
            case EVENT_FALLING_FRAGMENTS:
                DoCast(me, SPELL_FALLING_FRAGMENT_PERIODIC);
                events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, 5000, 0, PHASE_TWO);
                break;
            case EVENT_BLACK_BLOOD_OF_THE_EARTH:
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                Talk(TALK_BLACK_BLOOD_OF_THE_EARTH);
                DoCast(me, SPELL_BLACK_BLOOD_OF_THE_EARTH);
                events.ScheduleEvent(EVENT_BLACK_BLOOD_ENDS, 15500, 0, PHASE_TWO);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_REMOVE_CLIENT_CONTROL | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                break;
            }
            case EVENT_BLACK_BLOOD_ENDS:
                RemoveFragments(false);
                summons.DespawnEntry(NPC_WORLD_TRIGGER_VISUAL);
                events.SetPhase(PHASE_ONE);
                if (!IsHeroic())
                    events.ScheduleEvent(EVENT_CRUSH_ARMOR, urand(5000, 6000), 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_STOMP, 19000, 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, 26000, 0, PHASE_ONE);
                events.ScheduleEvent(EVENT_EARTHEN_VOTEX, 74000, 0, PHASE_ONE);
                break;
            case EVENT_CRUSH_ARMOR:
                DoCastVictim(SPELL_CRUSH_ARMOR);
                events.ScheduleEvent(EVENT_CRUSH_ARMOR, 6000, 0, PHASE_ONE);
                break;
            case EVENT_BERSERK:
                DoCast(me, SPELL_BERSERK, true);
                break;
            case EVENT_REACT_AGGRESSIVE:
                me->SetReactState(REACT_AGGRESSIVE);
                me->SetInCombatWithZone();
                break;
            default:
                break;
            }
        }
        if (events.IsInPhase(PHASE_ONE))
            DoMeleeAttackIfReady();
    }

  private:
    bool _kocromSummoned;
    uint32 currentVehicleTarget;
    bool firstPhase;
    uint8 crystalCount;
    uint8 stompCount;
    float oldOrientation;
};

struct boss_kohcrom : public ScriptedAI
{
    boss_kohcrom(Creature* creature) : ScriptedAI(creature), summons(me) { instance = me->GetInstanceScript(); }

    void IsSummonedBy(Unit* summoner) override
    {
        firstPhase = true;
        firstCrystal = true;
        oldOrientation = summoner->GetOrientation();
    }

    void JustSummoned(Creature* summon) override
    {
        switch (summon->GetEntry())
        {
        case NPC_WORLD_TRIGGER_VISUAL:
            summon->CastSpell(summon, SPELL_BLACK_BLOOD_GROUND_VISUAL, true);
            summon->m_Events.AddEvent(new VortexVisualEvent(summon), summon->m_Events.CalculateTime(3500));
            break;
        default:
            if (Creature* morchok = instance->GetCreature(DATA_MORCHOK))
                morchok->AI()->JustSummoned(summon);
            break;
        }
    }

    void DamageTaken(Unit* attacker, uint32& damage) override
    {
        if (!me->HasAura(SPELL_FURIOUS) && me->HealthBelowPctDamaged(20, damage))
            DoCast(me, SPELL_FURIOUS, true);

        if (IsHeroic())
        {
            if (Creature* morchok = instance->GetCreature(DATA_MORCHOK))
            {
                if (me->HealthBelowPct(2) && !morchok->HealthBelowPct(2))
                    damage = 0;
                else
                {
                    if (attacker != morchok)
                    {
                        damage /= 2;
                        Unit::DealDamage(me, morchok, damage);
                    }
                }
            }
        }
        me->SetObjectScale(std::max((me->GetHealthPct() / 100), 0.10f));
    }

    void JustEnteredCombat(Unit* victim) override
    {
        crystalCount = 0;
        Talk(TALK_AGGRO);
        instance->SendEncounterUnit(ENCOUNTER_FRAME_ENGAGE, me);
        if (Creature* morchok = instance->GetCreature(DATA_MORCHOK))
        {
            events.SetPhase(PHASE_ONE);
            events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, morchok->AI()->GetData(EVENT_RESONATING_CRYSTAL) + (Is25ManRaid() ? 5000 : 6000), 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_EARTHEN_VOTEX, morchok->AI()->GetData(EVENT_EARTHEN_VOTEX) + 500, 0, PHASE_ONE);
            events.ScheduleEvent(EVENT_BERSERK, morchok->AI()->GetData(EVENT_BERSERK) + (Is25ManRaid() ? 5000 : 6000), 0, PHASE_ALL);
            DoZoneInCombat();
        }
    }

    void JustDied(Unit* killer) override
    {
        RemoveFragments();
        summons.DespawnAll();
        instance->SendEncounterUnit(ENCOUNTER_FRAME_DISENGAGE, me);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(TALK_KILLING_A_PLAYER);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == EFFECT_MOTION_TYPE && id == EVENT_JUMP)
        {
            me->SetFacingTo(oldOrientation);
            events.ScheduleEvent(EVENT_REACT_AGGRESSIVE, 2500);
        }
    }

    void DoAction(int32 const action) override
    {
        if (action == ACTION_STOMP)
            events.ScheduleEvent(EVENT_STOMP, (Is25ManRaid() ? 5000 : 6000), 0, PHASE_ONE);
    }

    void RemoveFragments()
    {
        std::list<GameObject*> fallingFragments;
        GetGameObjectListWithEntryInGrid(fallingFragments, me, GO_FALLING_FRAGMENT, 300.0f);
        for (auto itr = fallingFragments.begin(); itr != fallingFragments.end(); ++itr)
        {
            if (GameObject* fallingFragment = *itr)
            {
                if (fallingFragment->GetOwner() == me)
                {
                    fallingFragment->UseDoorOrButton();
                    fallingFragment->Delete(2000);
                }
            }
        }
    }

    void UpdateAI(uint32 const diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventid = events.ExecuteEvent())
        {
            switch (eventid)
            {
            case EVENT_STOMP:
                DoCast(me, SPELL_STOMP);
                break;
            case EVENT_RESONATING_CRYSTAL:
            {
                Talk(TALK_SUMMON_RESONATING_CRYSTAL);
                float angle = frand(0.0f, 2.0f * M_PI);
                float dist = frand(30.0f, 40.0f);
                float tempAngle = me->NormalizeOrientation(angle);
                Position pos(*me);
                me->MovePosition(pos, dist, tempAngle);
                me->CastSpell(pos, SPELL_RESONATING_CRYSTAL_SUMMON, true);
                if (firstCrystal)
                    events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, 12000, 0, PHASE_ONE);
                firstCrystal = false;
                break;
            }
            case EVENT_EARTHEN_VOTEX:
                if (Creature* morchok = instance->GetCreature(DATA_MORCHOK))
                    morchok->AI()->SetData(DATA_VEHICLE_TARGET, VEHICLE_TARGET_KOHCROM);

                DoCast(me, SPELL_EARTHEN_VORTEX);
                events.SetPhase(PHASE_TWO);
                events.ScheduleEvent(EVENT_FALLING_FRAGMENTS, 100, 0, PHASE_TWO);
                crystalCount = 0;
                break;
            case EVENT_FALLING_FRAGMENTS:
                DoCast(me, SPELL_FALLING_FRAGMENT_PERIODIC);
                events.ScheduleEvent(EVENT_BLACK_BLOOD_OF_THE_EARTH, 5000, 0, PHASE_TWO);
                break;
            case EVENT_BLACK_BLOOD_OF_THE_EARTH:
            {
                DoCast(me, SPELL_BLACK_BLOOD_OF_THE_EARTH);
                events.ScheduleEvent(EVENT_BLACK_BLOOD_ENDS, 15500, 0, PHASE_TWO);
                break;
            }
            case EVENT_BLACK_BLOOD_ENDS:
                RemoveFragments();
                summons.DespawnEntry(NPC_WORLD_TRIGGER_VISUAL);
                if (Creature* morchok = instance->GetCreature(DATA_MORCHOK))
                {
                    firstCrystal = true;
                    me->SetReactState(REACT_AGGRESSIVE);
                    events.SetPhase(PHASE_ONE);
                    events.ScheduleEvent(EVENT_RESONATING_CRYSTAL, 45000, 0, PHASE_ONE);
                    events.ScheduleEvent(EVENT_EARTHEN_VOTEX, morchok->AI()->GetData(EVENT_EARTHEN_VOTEX) + 500, 0, PHASE_ONE);
                }
                break;
            case EVENT_BERSERK:
                DoCast(me, SPELL_BERSERK, true);
                break;
            case EVENT_REACT_AGGRESSIVE:
                me->SetReactState(REACT_AGGRESSIVE);
                me->SetInCombatWithZone();
                break;
            default:
                break;
            }
        }
        if (events.IsInPhase(PHASE_ONE))
            DoMeleeAttackIfReady();
    }

  private:
    EventMap events;
    InstanceScript* instance;
    SummonList summons;
    bool firstCrystal;
    bool firstPhase;
    uint8 crystalCount;
    float oldOrientation;
};

struct npc_ds_earthen_vortex_vehicle : public PassiveAI
{
    npc_ds_earthen_vortex_vehicle(Creature* creature) : PassiveAI(creature) { instance = me->GetInstanceScript(); }

    class EjectPassengerEvent : public BasicEvent
    {
      public:
        EjectPassengerEvent(Creature* owner) : _owner(owner) {}

        bool Execute(uint64 execTime, uint32 /*diff*/)
        {
            if (Vehicle* veh = _owner->GetVehicleKit())
                veh->RemoveAllPassengers();
            return true;
        }

      private:
        Creature* _owner;
    };

    void IsSummonedBy(Unit* summoner)
    {
        me->DespawnOrUnsummon(15000);
        me->m_Events.AddEvent(new EjectPassengerEvent(me), me->m_Events.CalculateTime(5000));
        summoner->CastSpell(me, SPELL_EARTHEN_VORTEX_RIDE_VEHICLE, true);
        DoCast(me, SPELL_BURROW, true);

        if (Creature* morchok = instance->GetCreature(DATA_MORCHOK))
        {
            if (morchok->AI()->GetData(DATA_VEHICLE_TARGET) == VEHICLE_TARGET_MORCHOK)
                me->GetMotionMaster()->MovePoint(0, morchok->GetPositionX(), morchok->GetPositionY(), morchok->GetPositionZ());
            else if (Unit* kohcrom = me->FindNearestCreature(NPC_KOHCROM, 500.00f))
                me->GetMotionMaster()->MovePoint(0, kohcrom->GetPositionX(), kohcrom->GetPositionY(), kohcrom->GetPositionZ());
        }
    }

  private:
    InstanceScript* instance;
};

class spell_ds_target_selection : public SpellScript
{
    std::list<WorldObject*> unauraTargets;

    bool Validate(SpellInfo const* /*spellInfo*/)
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_DANGER) || !sSpellMgr->GetSpellInfo(SPELL_WARNING) || !sSpellMgr->GetSpellInfo(SPELL_SAFE))
            return false;
        return true;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        uint8 targetCount = GetSpellInfo()->Id == SPELL_TARGET_SELECTION ? 3 : 7;
        uint8 count = 0;

        targets.remove_if([](WorldObject* target) { return !target->IsPlayer(); });

        if (!targets.empty())
            targets.sort(Firelands::ObjectDistanceOrderPred(GetCaster()));

        for (auto itr = targets.begin(); itr != targets.end(); ++itr)
        {
            if (++count > targetCount)
                unauraTargets.push_back((*itr));
        }

        if (targets.size() > targetCount)
            targets.resize(targetCount);

        float npcSize = 2.00f;
        bool is25ManRaid = GetCaster()->GetMap()->Is25ManRaid();
        for (auto target : targets)
        {
            float dist2D = target->GetDistance2d(GetCaster());
            if (dist2D > 20.0f)
                npcSize += (is25ManRaid ? 0.285f : 0.666f);
            else if (dist2D < 20.0f && dist2D > 5.0f)
                npcSize += (is25ManRaid ? 0.142f : 0.333f);
        }
        GetCaster()->SetObjectScale(npcSize);
    }

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            float dist2D = target->GetDistance2d(GetCaster());
            if (dist2D > 20.0f)
                GetCaster()->CastSpell(target, SPELL_DANGER, true);
            else if (dist2D < 20.0f && dist2D > 5.0f)
                GetCaster()->CastSpell(target, SPELL_WARNING, true);
            else
                GetCaster()->CastSpell(target, SPELL_SAFE, true);
        }
    }

    void RemoveAuras()
    {
        for (std::list<WorldObject*>::iterator itr = unauraTargets.begin(); itr != unauraTargets.end(); ++itr)
        {
            if (Unit* unit = (*itr)->ToUnit())
            {
                unit->RemoveAurasDueToSpell(SPELL_DANGER, GetCaster()->GetGUID());
                unit->RemoveAurasDueToSpell(SPELL_WARNING, GetCaster()->GetGUID());
                unit->RemoveAurasDueToSpell(SPELL_SAFE, GetCaster()->GetGUID());
            }
        }
    }

    void Register()
    {
        OnObjectAreaTargetSelect.Register(&spell_ds_target_selection::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        OnEffectHitTarget.Register(&spell_ds_target_selection::HandleDummy, EFFECT_1, SPELL_EFFECT_DUMMY);
        OnHit.Register(&spell_ds_target_selection::RemoveAuras);
    }
};

class spell_ds_resonating_crystal_periodic : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/)
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_CRYSTAL_EXPLOSION))
            return false;

        return true;
    }

    void HandleTriggerSpell(AuraEffect const* aurEff)
    {
        if (aurEff->GetTickNumber() >= 12)
        {
            if (Creature* crystal = GetTarget()->ToCreature())
            {
                PreventDefaultAction();
                crystal->CastSpell(nullptr, SPELL_CRYSTAL_EXPLOSION, true);
                crystal->DespawnOrUnsummon(1000);
                crystal->RemoveAurasDueToSpell(GetId());
            }
        }
    }

    void Register() { OnEffectPeriodic.Register(&spell_ds_resonating_crystal_periodic::HandleTriggerSpell, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL); }
};

class spell_ds_resonating_crystal_explosion : public SpellScript
{
    std::list<WorldObject*> sharedTargets;

    bool Validate(SpellInfo const* /*spellInfo*/)
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_DANGER) || !sSpellMgr->GetSpellInfo(SPELL_WARNING) || !sSpellMgr->GetSpellInfo(SPELL_SAFE))
            return false;
        return true;
    }

    bool Load()
    {
        danger = 0;
        warning = 0;
        safe = 0;
        return true;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            targets.remove_if(
                [caster](WorldObject* target)
                {
                    if (Player* player = target->ToPlayer())
                        if (player->HasAura(SPELL_DANGER, caster->GetGUID()) || player->HasAura(SPELL_WARNING, caster->GetGUID()) || player->HasAura(SPELL_SAFE, caster->GetGUID()))
                            return false;
                    return true;
                });
        }
        sharedTargets = targets;
    }

    void FilterTargetsShared(std::list<WorldObject*>& targets) { targets = sharedTargets; }

    void CountBuffs(SpellEffIndex /*effIndex*/)
    {
        for (auto itr = sharedTargets.begin(); itr != sharedTargets.end(); itr++)
        {
            if (Player* player = (*itr)->ToPlayer())
            {
                if (player->HasAura(SPELL_DANGER, GetCaster()->GetGUID()))
                    danger++;
                else if (player->HasAura(SPELL_WARNING, GetCaster()->GetGUID()))
                    warning++;
                else if (player->HasAura(SPELL_SAFE, GetCaster()->GetGUID()))
                    safe++;
            }
        }
    }

    void HandleDamage(SpellEffIndex effIndex)
    {
        int32 baseDamage = GetSpellInfo()->Effects[effIndex].CalcValue(GetCaster());
        uint8 targetCount = danger + warning + safe;
        int32 sharedDamage = ((baseDamage * danger) + ((baseDamage / 2) * warning) + ((baseDamage / 3) * safe)) / targetCount;
        SetHitDamage(sharedDamage);

        if (Unit* target = GetHitUnit())
        {
            target->RemoveAurasDueToSpell(SPELL_DANGER, GetCaster()->GetGUID());
            target->RemoveAurasDueToSpell(SPELL_WARNING, GetCaster()->GetGUID());
            target->RemoveAurasDueToSpell(SPELL_SAFE, GetCaster()->GetGUID());
        }
    }

  private:
    uint8 danger;
    uint8 warning;
    uint8 safe;

    void Register()
    {
        OnObjectAreaTargetSelect.Register(&spell_ds_resonating_crystal_explosion::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        OnObjectAreaTargetSelect.Register(&spell_ds_resonating_crystal_explosion::FilterTargetsShared, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        OnObjectAreaTargetSelect.Register(&spell_ds_resonating_crystal_explosion::FilterTargetsShared, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
        OnEffectLaunch.Register(&spell_ds_resonating_crystal_explosion::CountBuffs, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
        OnEffectHitTarget.Register(&spell_ds_resonating_crystal_explosion::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

class spell_ds_falling_fragments_periodic : public AuraScript
{
    bool Validate(SpellInfo const* /*spellInfo*/)
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_FALLING_FRAGMENT_MISSILE))
            return false;
        return true;
    }

    void HandleTriggerSpell(AuraEffect const* aurEff)
    {
        uint8 maxAttemps = 0;
        while (maxAttemps < 20)
        {
            float angle = frand(0.0f, 2.0f * M_PI);
            float tempAngle = Position::NormalizeOrientation(angle);
            bool nearObject = false;
            Position pos(*GetCaster());

            GetCaster()->GetNearPosition(35.0f, tempAngle);
            std::list<GameObject*> fragmentCollision;
            GetGameObjectListWithEntryInGrid(fragmentCollision, GetCaster(), GO_FALLING_FRAGMENT, 50.0f);
            for (GameObject* gob : fragmentCollision)
            {
                if (gob->GetExactDist2d(&pos) < 4.0f)
                {
                    nearObject = true;
                    break;
                }
            }

            if (!nearObject)
            {
                GetCaster()->CastSpell(pos, SPELL_FALLING_FRAGMENT_MISSILE, true);
                break;
            }
            maxAttemps++;
        }

        if (rand() % 100 < 40)
        {
            uint8 maxAttemps = 0;
            while (maxAttemps < 20)
            {
                float angle = frand(0.0f, 2.0f * M_PI);
                float tempAngle = Position::NormalizeOrientation(angle);
                bool nearObject = false;
                Position pos(*GetCaster());
                GetCaster()->GetNearPosition(35.0f, tempAngle);
                std::list<GameObject*> fragmentCollision;
                GetGameObjectListWithEntryInGrid(fragmentCollision, GetCaster(), GO_FALLING_FRAGMENT, 50.0f);
                for (GameObject* gob : fragmentCollision)
                {
                    if (gob->GetExactDist2d(&pos) < 4.0f)
                    {
                        nearObject = true;
                        break;
                    }
                }

                if (!nearObject)
                {
                    GetCaster()->CastSpell(pos, SPELL_FALLING_FRAGMENT_MISSILE, true);
                    break;
                }
                maxAttemps++;
            }
        }
    }

    void Register() { OnEffectPeriodic.Register(&spell_ds_falling_fragments_periodic::HandleTriggerSpell, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL); }
};

class spell_ds_earthen_vortex_teleport : public SpellScript
{
    std::list<WorldObject*> sharedTargets;

    bool Validate(SpellInfo const* /*spellInfo*/)
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_EARTHEN_VORTEX))
            return false;
        return true;
    }

    void FilterEffect0(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            Creature* morchokOrKohchrom = caster->FindNearestCreature((caster->GetEntry() == NPC_MORCHOK ? NPC_KOHCROM : NPC_MORCHOK), 500.00f);
            targets.remove_if(
                [caster, morchokOrKohchrom](WorldObject* target)
                {
                    if ((target->ToUnit() && target->ToUnit()->GetVehicle()))
                        return true;

                    if (caster->GetMap()->IsHeroic() && morchokOrKohchrom)
                        return caster->GetDistance2d(target) > morchokOrKohchrom->GetDistance2d(target);
                    return false;
                });
        }
        sharedTargets = targets;
    }

    void FilterEffect1(std::list<WorldObject*>& targets) { targets.clear(); }

    void FilterEffect2(std::list<WorldObject*>& targets) { targets = sharedTargets; }

    void Register()
    {
        OnObjectAreaTargetSelect.Register(&spell_ds_earthen_vortex_teleport::FilterEffect0, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        OnObjectAreaTargetSelect.Register(&spell_ds_earthen_vortex_teleport::FilterEffect1, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
        OnObjectAreaTargetSelect.Register(&spell_ds_earthen_vortex_teleport::FilterEffect2, EFFECT_2, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_ds_black_blood_of_the_earth_periodic : public AuraScript
{
    float spawnDist;

    bool Validate(SpellInfo const* /*spellInfo*/)
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_BLACK_BLOOD_OF_THE_EARTH))
            return false;
        return true;
    }

    bool Load()
    {
        spawnDist = 8.0f;
        return true;
    }

    void HandleTriggerSpell(AuraEffect const* aurEff)
    {
        if (aurEff->GetTickNumber() >= 10)
            return;

        if (Unit* caster = GetCaster())
        {
            float angle = frand(0.0f, 2.0f * M_PI);
            float step = float(M_PI) / 16.0f;
            for (uint8 i = 0; i < 32; ++i)
            {
                float tempAngle = Position::NormalizeOrientation(angle);
                Position pos(*caster);
                caster->MovePosition(pos, spawnDist, tempAngle);
                caster->SummonCreature(NPC_WORLD_TRIGGER_VISUAL, pos, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 15500);
                angle += step;
            }
            spawnDist += 8.0f;
        }
    }

    void Register() { OnEffectPeriodic.Register(&spell_ds_black_blood_of_the_earth_periodic::HandleTriggerSpell, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL); }
};

class ExtraLOSFilter
{
  public:
    explicit ExtraLOSFilter(Unit* caster, std::list<GameObject*> const& collisionList) : _caster(caster), _collisionList(collisionList) {}

    bool operator()(WorldObject* unit) const
    {
        for (auto itr = _collisionList.begin(); itr != _collisionList.end(); ++itr)
            if ((*itr)->IsInBetween(_caster, unit, 2.9f))
                return true;
        return false;
    }

  private:
    Unit* _caster;
    std::list<GameObject*> _collisionList;
};

class spell_ds_black_blood_of_the_earth_damage : public SpellScript
{
    std::list<WorldObject*> sharedTargets;

    bool Validate(SpellInfo const* /*spellInfo*/)
    {
        if (!sSpellMgr->GetSpellInfo(SPELL_BLACK_BLOOD_OF_THE_EARTH))
            return false;
        return true;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (Unit* caster = GetCaster())
        {
            std::list<GameObject*> fragmentCollision;
            GetGameObjectListWithEntryInGrid(fragmentCollision, GetCaster(), GO_FALLING_FRAGMENT, 90.0f);
            targets.remove_if(ExtraLOSFilter(GetCaster(), fragmentCollision));
            targets.remove_if(
                [caster](WorldObject* target)
                {
                    if (AuraEffect* aurEff = caster->GetAuraEffect(SPELL_BLACK_BLOOD_OF_THE_EARTH, EFFECT_0, caster->GetGUID()))
                    {
                        float dist = std::min(aurEff->GetTickNumber() * 8.0f, 90.0f);
                        if (target->GetExactDist2d(caster->GetPositionX(), caster->GetPositionY()) > dist)
                            return true;
                    }
                    return false;
                });
        }
        sharedTargets = targets;
    }

    void FilterTargetsShared(std::list<WorldObject*>& targets) { targets = sharedTargets; }

    void Register()
    {
        OnObjectAreaTargetSelect.Register(&spell_ds_black_blood_of_the_earth_damage::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENEMY);
        OnObjectAreaTargetSelect.Register(&spell_ds_black_blood_of_the_earth_damage::FilterTargetsShared, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

void AddSC_boss_morchok()
{
    RegisterDragonSoulCreatureAI(boss_morchok);
    RegisterDragonSoulCreatureAI(boss_kohcrom);
    RegisterDragonSoulCreatureAI(npc_ds_earthen_vortex_vehicle);
    RegisterSpellScript(spell_ds_target_selection);
    RegisterSpellScript(spell_ds_resonating_crystal_periodic);
    RegisterSpellScript(spell_ds_resonating_crystal_explosion);
    RegisterSpellScript(spell_ds_falling_fragments_periodic);
    RegisterSpellScript(spell_ds_earthen_vortex_teleport);
    RegisterSpellScript(spell_ds_black_blood_of_the_earth_periodic);
    RegisterSpellScript(spell_ds_black_blood_of_the_earth_damage);
}
