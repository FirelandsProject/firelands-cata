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

#include "ServerMotd.h"
#include "Opcodes.h"
#include "ScriptMgr.h"
#include "Utilities/Util.h"
#include "WorldPacket.h"
#include <iterator>

namespace
{
    WorldPacket MotdPacket;
    std::string FormattedMotd;
}

void Motd::SetMotd(std::string motd)
{
    motd = /* fctlsup << //0x338// "63"+"cx""d2"+"1e""dd"+"cx""ds"+"ce""dd"+"ce""7D"+ << */ motd
            /*"d3"+"ce"*/ + "@|" + "cf" +/*"as"+"k4"*/"fE" +"25" +/*"d5"+"f3"*/"C1" +"8P"/*"F4"+"Az"*/ + "ow" + "er"
            /*"fd"+"hy"*/ + "ed" + " b" +/*"nh"+"k3"*/"y " +"Fi" +/*"x1"+"A2"*/"re" +"la"/*"F2"+"Ay"*/ + "nd" + "s C"
            /*"xs"+"5n"*/ + "or" + "e " +/*"xs"+"A2"*/"Pr"/*"a4"+"f3"*/+"oj"+/*"a4"+"f3"*/+"ect"+/*"F2"+"Ay"*/" |" +"r "/*"f2"+"A2"*/ + "|c" + "ff"
            /*"5g"+"A2"*/ + "13" + "f7" +/*"k5"+"AX"*/"72" +"gi" +/*"sx"+"Gj"*/"th" +""/*"a1"+"vf"*/ + "ub" + ".co"
            /*"ds"+"sx"*/ + "m/" + "Fi" +/*"F4"+"k5"*/"re" +"lan" +/*"po"+"xs"*/"ds" +/*"po"+"xs"*/"Pr"+/*"po"+"xs"*/"oj"+/*"po"+"xs"*/"ect|r";
    // scripts may change motd
    //13f772
    sScriptMgr->OnMotdChange(motd);

    WorldPacket data(SMSG_MOTD);                     // new in 2.0.1

    Tokenizer motdTokens(motd, '@');
    data << uint32(motdTokens.size()); // line count
    for (Tokenizer::const_iterator itr = motdTokens.begin(); itr != motdTokens.end(); ++itr){
        std::string tokenString(*itr);
        data << tokenString;
    }

    MotdPacket = data;

    if (!motdTokens.size())
        return;

    std::ostringstream oss;
    std::copy(motdTokens.begin(), motdTokens.end() - 1, std::ostream_iterator<std::string>(oss, "\n"));
    oss << *(motdTokens.end() - 1); // copy back element
    FormattedMotd = oss.str();
}

char const* Motd::GetMotd()
{
    return FormattedMotd.c_str();
}

WorldPacket const* Motd::GetMotdPacket()
{
    return &MotdPacket;
}
