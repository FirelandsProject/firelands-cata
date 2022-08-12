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

#include "AuthenticationPackets.h"

#include "HmacHash.h"

bool WorldPackets::Auth::EarlyProcessClientPacket::ReadNoThrow() {
  try {
    Read();
    return true;
  } catch (ByteBufferPositionException const& /*ex*/) {
  }

  return false;
}

void WorldPackets::Auth::Ping::Read() {
  _worldPacket >> Latency;
  _worldPacket >> Serial;
}

WorldPacket const* WorldPackets::Auth::Pong::Write() {
  _worldPacket << uint32(Serial);
  return &_worldPacket;
}

WorldPacket const* WorldPackets::Auth::AuthChallenge::Write() {
  _worldPacket.append(DosChallenge.data(), DosChallenge.size());
  _worldPacket << uint32(Challenge);
  _worldPacket << uint8(DosZeroBits);
  return &_worldPacket;
}

void WorldPackets::Auth::AuthSession::Read() {
  uint32 addonDataSize;

  _worldPacket >> LoginServerID;
  _worldPacket >> BattlegroupID;
  _worldPacket >> LoginServerType;
  _worldPacket >> Digest[10];
  _worldPacket >> Digest[18];
  _worldPacket >> Digest[12];
  _worldPacket >> Digest[5];

  _worldPacket >> DosResponse;

  _worldPacket >> Digest[15];
  _worldPacket >> Digest[9];
  _worldPacket >> Digest[19];
  _worldPacket >> Digest[4];
  _worldPacket >> Digest[7];
  _worldPacket >> Digest[16];
  _worldPacket >> Digest[3];

  _worldPacket >> Build;

  _worldPacket >> Digest[8];

  _worldPacket >> RealmID;
  _worldPacket >> BuildType;

  _worldPacket >> Digest[17];
  _worldPacket >> Digest[6];
  _worldPacket >> Digest[0];
  _worldPacket >> Digest[1];
  _worldPacket >> Digest[11];

  _worldPacket >> LocalChallenge;

  _worldPacket >> Digest[2];

  _worldPacket >> RegionID;

  _worldPacket >> Digest[14];
  _worldPacket >> Digest[13];

  _worldPacket >> addonDataSize;

  if (addonDataSize) {
    AddonInfo.resize(addonDataSize);
    _worldPacket.read(AddonInfo.contents(), addonDataSize);
  }

  UseIPv6 = _worldPacket.ReadBit();  // UseIPv6
  uint8 accountNameLength = _worldPacket.ReadBits(12);
  Account = _worldPacket.ReadString(accountNameLength);
}

WorldPacket const* WorldPackets::Auth::AuthResponse::Write() {
  _worldPacket.WriteBit(WaitInfo.has_value());

  if (WaitInfo) _worldPacket.WriteBit(WaitInfo->HasFCM);

  _worldPacket.WriteBit(SuccessInfo.has_value());
  _worldPacket.FlushBits();

  if (SuccessInfo) {
    _worldPacket << uint32(SuccessInfo->TimeRemain);
    _worldPacket << uint8(SuccessInfo->ActiveExpansionLevel);
    _worldPacket << uint32(SuccessInfo->TimeSecondsUntilPCKick);
    _worldPacket << uint8(SuccessInfo->AccountExpansionLevel);
    _worldPacket << uint32(SuccessInfo->TimeRested);
    _worldPacket << uint8(SuccessInfo->TimeOptions);
  }

  _worldPacket << uint8(Result);

  if (WaitInfo) _worldPacket << uint32(WaitInfo->WaitCount);

  return &_worldPacket;
}

WorldPacket const* WorldPackets::Auth::WaitQueueUpdate::Write() {
  _worldPacket << uint32(WaitInfo.WaitCount);
  _worldPacket.WriteBit(WaitInfo.HasFCM);
  return &_worldPacket;
}

void WorldPackets::Auth::AuthContinuedSession::Read() {
  _worldPacket >> Key;
  _worldPacket >> DosResponse;

  _worldPacket >> Digest[5];
  _worldPacket >> Digest[2];
  _worldPacket >> Digest[6];
  _worldPacket >> Digest[10];
  _worldPacket >> Digest[8];
  _worldPacket >> Digest[17];
  _worldPacket >> Digest[11];
  _worldPacket >> Digest[15];
  _worldPacket >> Digest[7];
  _worldPacket >> Digest[1];
  _worldPacket >> Digest[4];
  _worldPacket >> Digest[16];
  _worldPacket >> Digest[0];
  _worldPacket >> Digest[12];
  _worldPacket >> Digest[14];
  _worldPacket >> Digest[13];
  _worldPacket >> Digest[18];
  _worldPacket >> Digest[9];
  _worldPacket >> Digest[19];
  _worldPacket >> Digest[3];
}
