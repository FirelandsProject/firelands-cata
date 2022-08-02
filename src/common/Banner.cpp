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

#include "Banner.h"
#include "GitRevision.h"
#include "StringFormat.h"

void Firelands::Banner::Show(char const* applicationName, void(*log)(char const* text), void(*logExtraInfo)())
{
    log(Firelands::StringFormat("%s (%s)", GitRevision::GetFullVersion(), applicationName).c_str());
    log("<Ctrl-C> to stop.\n");
    log(" _______  ___   ______    _______  ___      _______  __    _  ______   _______ ");
    log("|       ||   | |    _ |  |       ||   |    |   _   ||  |  | ||      | |       |");
    log("|    ___||   | |   | ||  |    ___||   |    |  |_|  ||   |_| ||  _    ||  _____|");
    log("|   |___ |   | |   |_||_ |   |___ |   |    |       ||       || | |   || |_____ ");
    log("|    ___||   | |    __  ||    ___||   |___ |       ||  _    || |_|   ||_____  |");
    log("|   |    |   | |   |  | ||   |___ |       ||   _   || | |   ||       | _____| |");
    log("|___|    |___| |___|  |_||_______||_______||__| |__||_|  |__||______| |_______|");
    log("                                           _______  _______  ______    _______ ");
    log("                                          |       ||       ||    _ |  |       |");
    log("                                          |       ||   _   ||   | ||  |    ___|");
    log("                                          |       ||  | |  ||   |_||_ |   |___ ");
    log("                                          |      _||  |_|  ||    __  ||    ___|");
    log("                                          |     |_ |       ||   |  | ||   |___ ");
    log("                                          |_______||_______||___|  |_||_______|");
    log("https://github.com/FirelandsProject                                           \n");

    if (logExtraInfo)
        logExtraInfo();
}
