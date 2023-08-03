/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "MovementPacketBuilder.h"
#include "MoveSpline.h"
#include "WorldPacket.h"
#include "Object.h"

namespace Movement
{
    inline void operator << (ByteBuffer& b, const Vector3& v)
    {
        b << v.x << v.y << v.z;
    }

    inline void operator >> (ByteBuffer& b, Vector3& v)
    {
        b >> v.x >> v.y >> v.z;
    }

    void PacketBuilder::WriteCreateBits(MoveSpline const& moveSpline, ByteBuffer& data)
    {
        if (!data.WriteBit(!moveSpline.Finalized()))
            return;

        data.WriteBits(uint8(moveSpline.spline.mode()), 2);
        data.WriteBit(moveSpline.splineflags & (MoveSplineFlag::Parabolic | MoveSplineFlag::Animation));
        data.WriteBits(moveSpline.getPath().size(), 22);
        switch (moveSpline.splineflags & MoveSplineFlag::Mask_Final_Facing)
        {
            case MoveSplineFlag::Final_Target:
            {
                ObjectGuid targetGuid(moveSpline.facing.target);
                data.WriteBits(2, 2);
                data.WriteBit(targetGuid[4]);
                data.WriteBit(targetGuid[3]);
                data.WriteBit(targetGuid[7]);
                data.WriteBit(targetGuid[2]);
                data.WriteBit(targetGuid[6]);
                data.WriteBit(targetGuid[1]);
                data.WriteBit(targetGuid[0]);
                data.WriteBit(targetGuid[5]);
                break;
            }
            case MoveSplineFlag::Final_Angle:
                data.WriteBits(0, 2);
                break;
            case MoveSplineFlag::Final_Point:
                data.WriteBits(1, 2);
                break;
            default:
                data.WriteBits(3, 2);
                break;
        }

        data.WriteBit((moveSpline.splineflags & MoveSplineFlag::Parabolic) && moveSpline.effect_start_time < moveSpline.Duration());
        data.WriteBits(moveSpline.splineflags.raw(), 25);
    }

    void PacketBuilder::WriteCreateData(MoveSpline const& moveSpline, ByteBuffer& data)
    {
        if (!moveSpline.Finalized())
        {
            MoveSplineFlag const& splineFlags = moveSpline.splineflags;

            if ((splineFlags & MoveSplineFlag::Parabolic) && moveSpline.effect_start_time < moveSpline.Duration())
                data << moveSpline.vertical_acceleration;   // added in 3.1

            data << moveSpline.timePassed();

            if (splineFlags.final_angle)
                data << moveSpline.facing.angle;
            else if (splineFlags.final_target)
            {
                ObjectGuid facingGuid(moveSpline.facing.target);
                data.WriteByteSeq(facingGuid[5]);
                data.WriteByteSeq(facingGuid[3]);
                data.WriteByteSeq(facingGuid[7]);
                data.WriteByteSeq(facingGuid[1]);
                data.WriteByteSeq(facingGuid[6]);
                data.WriteByteSeq(facingGuid[4]);
                data.WriteByteSeq(facingGuid[2]);
                data.WriteByteSeq(facingGuid[0]);
            }

            uint32 nodes = moveSpline.getPath().size();
            for (uint32 i = 0; i < nodes; ++i)
            {
                data << float(moveSpline.getPath()[i].z);
                data << float(moveSpline.getPath()[i].x);
                data << float(moveSpline.getPath()[i].y);
            }

            if (splineFlags.final_point)
                data << moveSpline.facing.f.x << moveSpline.facing.f.z << moveSpline.facing.f.y;

            data << float(1.f);                             // splineInfo.duration_mod_next; added in 3.1
            data << moveSpline.Duration();
            if (splineFlags & (MoveSplineFlag::Parabolic | MoveSplineFlag::Animation))
                data << moveSpline.effect_start_time;       // added in 3.1

            data << float(1.f);                             // splineInfo.duration_mod; added in 3.1
        }

        if (!moveSpline.isCyclic())
        {
            Vector3 dest = moveSpline.FinalDestination();
            data << float(dest.z);
            data << float(dest.x);
            data << float(dest.y);
        }
        else
            data << Vector3::zero();

        data << moveSpline.GetId();
    }

    float PacketBuilder::GetFlightSplineSyncDist(MoveSpline const& moveSpline)
    {
        return (float)moveSpline.timePassed() / moveSpline.Duration();
    }
}
