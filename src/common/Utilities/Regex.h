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

#ifndef _Firelands_Regex_h__
#define _Firelands_Regex_h__

#ifndef FC_HAS_BROKEN_WSTRING_REGEX
#include <regex>
#define FC_REGEX_NAMESPACE std
#else
#include <boost/regex.hpp>
#define FC_REGEX_NAMESPACE boost
#endif

// regex compatibility layer, required for clang building with libstdc++-4.9
namespace Firelands
{
    using regex = FC_REGEX_NAMESPACE :: regex;
    using wregex = FC_REGEX_NAMESPACE :: wregex;

    using :: FC_REGEX_NAMESPACE :: regex_match;
    using :: FC_REGEX_NAMESPACE :: regex_search;
}

#endif // _Firelands_Regex_h__
