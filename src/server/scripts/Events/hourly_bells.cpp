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

#include "ScriptMgr.h"

#include "EventMap.h"
#include "GameObject.h"
#include "GameObjectAI.h"
#include "GameTime.h"

enum BellHourlySoundFX
{
    BELLTOLLHORDE      = 6595, // Undercity
    BELLTOLLTRIBAL     = 6675, // Orgrimmar/Thunderbluff
    BELLTOLLALLIANCE   = 6594, // Stormwind
    BELLTOLLNIGHTELF   = 6674, // Darnassus
    BELLTOLLDWARFGNOME = 7234, // Ironforge
    BELLTOLLKHARAZHAN  = 9154  // Kharazhan
};

enum BellHourlySoundZones
{
    TIRISFAL_ZONE            = 85,
    UNDERCITY_ZONE           = 1497,
    DUN_MOROGH_ZONE          = 1,
    IRONFORGE_ZONE           = 1537,
    TELDRASSIL_ZONE          = 141,
    DARNASSUS_ZONE           = 1657,
    ASHENVALE_ZONE           = 331,
    HILLSBRAD_FOOTHILLS_ZONE = 267,
    DUSKWOOD_ZONE            = 10
};

enum BellHourlyObjects
{
    GO_HORDE_BELL          = 175885,
    GO_ALLIANCE_BELL       = 176573,
    GO_KHARAZHAN_BELL      = 182064
};

enum BellHourlyMisc
{
    GAME_EVENT_HOURLY_BELLS = 73,
    EVENT_RING_BELL         = 1
};

struct hourly_bells : public GameObjectAI
{
    explicit hourly_bells(GameObject* go) : GameObjectAI(go), _soundId(0) { }

    void InitializeAI() override
    {
        uint32 zoneId = me->GetZoneId();

        switch (me->GetEntry())
        {
            case GO_HORDE_BELL:
            {
                switch (zoneId)
                {
                    case TIRISFAL_ZONE:
                    case UNDERCITY_ZONE:
                    case HILLSBRAD_FOOTHILLS_ZONE:
                    case DUSKWOOD_ZONE:
                        _soundId = BELLTOLLHORDE;  // undead bell sound
                        break;

                    default:
                        _soundId = BELLTOLLTRIBAL; // orc drum sound
                        break;
                }
                break;
            }

            case GO_ALLIANCE_BELL:
            {
                switch (zoneId)
                {
                    case IRONFORGE_ZONE:
                    case DUN_MOROGH_ZONE:
                        _soundId = BELLTOLLDWARFGNOME; // horn sound
                        break;

                    case DARNASSUS_ZONE:
                    case TELDRASSIL_ZONE:
                    case ASHENVALE_ZONE:
                        _soundId = BELLTOLLNIGHTELF;   // nightelf bell sound
                        break;

                    default:
                        _soundId = BELLTOLLALLIANCE;   // human bell sound
                }
                break;
            }

            case GO_KHARAZHAN_BELL:
            {
                _soundId = BELLTOLLKHARAZHAN;
                break;
            }
        }
    }

    void OnGameEvent(bool start, uint16 eventId) override
    {
        if (eventId == GAME_EVENT_HOURLY_BELLS && start)
        {
            time_t time = GameTime::GetGameTime();
            tm localTm;
            localtime_r(&time, &localTm);
            uint8 _rings = (localTm.tm_hour) % 12;
            _rings = (_rings == 0) ? 12 : _rings; // 00:00 and 12:00

            // Bell for Dwarf & Gnome is a single ring (horn)
            if (_soundId == BELLTOLLDWARFGNOME)
            {
                _rings = 1;
            }

            for (auto i = 0; i < _rings; ++i)
            {
                _events.ScheduleEvent(EVENT_RING_BELL, Seconds(i * 4 + 1));
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_RING_BELL:
                    me->PlayDirectSound(_soundId);
                    break;

                default:
                    break;
            }
        }
    }

    private:
        EventMap _events;
        uint32 _soundId;
};

void AddSC_event_hourly_bells()
{
    RegisterGameObjectAI(hourly_bells);
}
