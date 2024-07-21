#include "ScriptMgr.h"
#include "DBCStores.h"
#include "Player.h"

enum RazorfenKraulEntrance
{
    AREA_ID_RAZORFEN_KRAUL = 1717,
    AREA_ID_RAZORFEN_KRAUL_ENTRANCE = 5518
};

/*
 * Looks like Blizzard realized that they have fucked up because they used an instance WMO object for the open world entrance
 * of Razorfen Kraul. So they instead placed an area trigger in front of the instance to trigger the exploration part because
 * that instance WMO object does return instance interior data rather than what we need.
 */
class at_sb_razorfen_kraul_entrance : public AreaTriggerScript
{
  public:
    at_sb_razorfen_kraul_entrance() : AreaTriggerScript("at_sb_razorfen_kraul_entrance") {}

    bool OnTrigger(Player* player, AreaTriggerEntry const* /*areaTrigger*/)
    {
        // Yep, one is for the message and experience, one for the exploration bit for the achievement
        player->SetAreaExplored(AREA_ID_RAZORFEN_KRAUL);
        player->SetAreaExplored(AREA_ID_RAZORFEN_KRAUL_ENTRANCE);
        return true;
    }
};

void AddSC_southern_barrens() { new at_sb_razorfen_kraul_entrance(); }
