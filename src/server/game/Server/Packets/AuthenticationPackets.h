/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for
 * Copyright information
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

#ifndef AuthenticationPacketsWorld_h__
#define AuthenticationPacketsWorld_h__

#include <array>
#include <boost/asio/ip/tcp.hpp>

#include "BigNumber.h"
#include "ObjectMgr.h"
#include "Packet.h"
#include "SHA1.h"
#include "Util.h"

using boost::asio::ip::tcp;

namespace WorldPackets {
namespace Auth {
class EarlyProcessClientPacket : public ClientPacket {
 public:
  EarlyProcessClientPacket(OpcodeClient opcode, WorldPacket&& packet)
      : ClientPacket(opcode, std::move(packet)) {}

  bool ReadNoThrow();
};

class Ping final : public EarlyProcessClientPacket {
 public:
  Ping(WorldPacket&& packet)
      : EarlyProcessClientPacket(CMSG_PING, std::move(packet)) {}

  uint32 Latency = 0;
  uint32 Serial = 0;

 private:
  void Read();
};

class Pong final : public ServerPacket {
 public:
  Pong(uint32 serial) : ServerPacket(SMSG_PONG, 4), Serial(serial) {}

  WorldPacket const* Write() override;

  uint32 Serial = 0;
};

class AuthChallenge final : public ServerPacket {
 public:
  AuthChallenge() : ServerPacket(SMSG_AUTH_CHALLENGE, 32 + 4 + 1) {}

  WorldPacket const* Write() override;

  std::array<uint32, 8> DosChallenge = {};
  uint32 Challenge = 0;
  uint8 DosZeroBits = 0;
};

class AuthSession final : public EarlyProcessClientPacket {
 public:
  AuthSession(WorldPacket&& packet)
      : EarlyProcessClientPacket(CMSG_AUTH_SESSION, std::move(packet)) {
    Digest.fill(0);
  }

  uint32 BattlegroupID = 0;
  int8 LoginServerType = 0;  ///< Auth type used - 0 GRUNT, 1 battle.net
  int8 BuildType = 0;
  uint32 RealmID = 0;
  uint16 Build = 0;
  uint32 LocalChallenge = 0;
  int32 LoginServerID = 0;
  uint32 RegionID = 0;
  uint64 DosResponse = 0;
  std::array<uint8, SHA_DIGEST_LENGTH> Digest;
  std::string Account;
  bool UseIPv6 = false;
  ByteBuffer AddonInfo;

 private:
  void Read() override;
};

struct AuthWaitInfo {
  uint32 WaitCount = 0;  ///< position of the account in the login queue
  bool HasFCM = false;   ///< true if the account has a forced character
                         ///< migration pending. @todo implement
};

struct AuthSuccessInfo {
  uint32 TimeRemain =
      0;  ///< the remaining game time that the account has in seconds. It is
          ///< not currently implemented and probably won't ever be.
  uint32 TimeRested =
      0;  ///< affects the return value of the GetBillingTimeRested() client API
          ///< call, it is the number of seconds you have left until the
          ///< experience points and loot you receive from creatures and quests
          ///< is reduced. It is only used in the Asia region in retail, it's
          ///< not implemented inFCand will probably never be.
  uint32 TimeSecondsUntilPCKick = 0;  ///< @todo research
  uint8 AccountExpansionLevel =
      0;  ///< the current expansion of this account, the possible values are in
          ///< @ref Expansions
  uint8 ActiveExpansionLevel = 0;  ///< the current server expansion, the
                                   ///< possible values are in @ref Expansions
  uint8 TimeOptions =
      0;  ///< controls the behavior of the client regarding billing, used in
          ///< Asia realms, as they don't have monthly subscriptions, possible
          ///< values are in @ref BillingPlanFlags. It is not currently
          ///< implemented and will probably never be.
};

class AuthResponse final : public ServerPacket {
 public:
  AuthResponse() : ServerPacket(SMSG_AUTH_RESPONSE) {}

  WorldPacket const* Write() override;

  Optional<AuthSuccessInfo>
      SuccessInfo;  ///< contains the packet data in case that it has account
                    ///< information, otherwise its contents are undefined.
  Optional<AuthWaitInfo> WaitInfo;  ///< contains the queue wait information in
                                    ///< case the account is in the login queue.
  uint8 Result = 0;  ///< the result of the authentication process, possible
                     ///< values are @ref ResponseCodes
};

class WaitQueueUpdate final : public ServerPacket {
 public:
  WaitQueueUpdate() : ServerPacket(SMSG_WAIT_QUEUE_UPDATE, 4 + 1) {}

  WorldPacket const* Write() override;

  AuthWaitInfo WaitInfo;
};

class WaitQueueFinish final : public ServerPacket {
 public:
  WaitQueueFinish() : ServerPacket(SMSG_WAIT_QUEUE_FINISH, 0) {}

  WorldPacket const* Write() override { return &_worldPacket; }
};

class AuthContinuedSession final : public EarlyProcessClientPacket {
 public:
  AuthContinuedSession(WorldPacket&& packet)
      : EarlyProcessClientPacket(CMSG_AUTH_CONTINUED_SESSION,
                                 std::move(packet)) {
    Digest.fill(0);
  }

  uint64 DosResponse = 0;
  uint64 Key = 0;
  std::array<uint8, SHA_DIGEST_LENGTH> Digest;

 private:
  void Read() override;
};
}  // namespace Auth
}  // namespace WorldPackets

#endif  // AuthenticationPacketsWorld_h__
