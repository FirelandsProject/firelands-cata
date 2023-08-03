/*
 * Copyright (C) 2022 Firelands <https://github.com/FirelandsProject/>
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

#ifndef NPCPackets_h__
#define NPCPackets_h__

#include "Packet.h"
#include "ObjectGuid.h"
#include "Optional.h"
#include <array>

namespace WorldPackets
{
    namespace NPC
    {
        // CMSG_BANKER_ACTIVATE
        // CMSG_BATTLEMASTER_HELLO
        // CMSG_BINDER_ACTIVATE
        // CMSG_GOSSIP_HELLO
        // CMSG_LIST_INVENTORY
        // CMSG_TRAINER_LIST
        class Hello final : public ClientPacket
        {
        public:
            Hello(WorldPacket&& packet) : ClientPacket(std::move(packet)) { }

            void Read() override;

            ObjectGuid Unit;
        };

        struct TrainerListSpell
        {
            int32 SpellID = 0;
            uint8 Usable = 0;
            int32 MoneyCost = 0;
            int32 ProfessionDialog = 0;
            int32 ProfessionButton = 0;
            uint8 ReqLevel = 0;
            int32 ReqSkillLine = 0;
            int32 ReqSkillRank = 0;
            std::array<int32, 2> ReqAbility = { };
        };

        class TrainerList final : public ServerPacket
        {
        public:
            TrainerList() : ServerPacket(SMSG_TRAINER_LIST, 150) { }

            WorldPacket const* Write() override;

            ObjectGuid TrainerGUID;
            int32 TrainerType = 0;
            int32 TrainerID = 0;
            std::vector<TrainerListSpell> Spells;
            std::string Greeting;
        };

        class TrainerBuySpell final : public ClientPacket
        {
        public:
            TrainerBuySpell(WorldPacket&& packet) : ClientPacket(CMSG_TRAINER_BUY_SPELL, std::move(packet)) { }

            void Read() override;

            ObjectGuid TrainerGUID;
            int32 TrainerID = 0;
            int32 SpellID = 0;
        };

        class TrainerBuyFailed final : public ServerPacket
        {
        public:
            TrainerBuyFailed() : ServerPacket(SMSG_TRAINER_BUY_FAILED, 8 + 4 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid TrainerGUID;
            int32 SpellID = 0;
            int32 TrainerFailedReason = 0;
        };

        class TrainerBuySucceeded final : public ServerPacket
        {
        public:
            TrainerBuySucceeded() : ServerPacket(SMSG_TRAINER_BUY_SUCCEEDED, 8 + 4) { }

            WorldPacket const* Write() override;

            ObjectGuid TrainerGUID;
            int32 SpellID = 0;
        };

        struct VendorItem
        {
            int32 MuID                              = 0;
            int32 Type                              = 0;
            int32 ItemID                            = 0;
            int32 ItemDisplayInfoID                 = 0;
            int32 Quantity                          = -1;
            uint32 Price                            = 0;
            int32 Durability                        = 0;
            int32 StackCount                        = 0;
            Optional<int32> ExtendedCostID;
            Optional<int32> PlayerConditionFailed;
        };

        class VendorInventory final : public ServerPacket
        {
        public:
            VendorInventory() : ServerPacket(SMSG_VENDOR_INVENTORY, 600) { }

            WorldPacket const* Write() override;

            uint8 Reason = 0;
            std::vector<VendorItem> Items;
            ObjectGuid Vendor;
        };
    }
}

#endif // NPCPackets_h__
