/*
 * This file is part of the FirelandsCore Project. See AUTHORS file for Copyright information
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

#ifndef SelectableAI_h__
#define SelectableAI_h__

#include "FactoryHolder.h"

class DBPermit
{
    public:
        virtual ~DBPermit() { }
        virtual bool IsScriptNameAllowedInDB() const = 0;
};

template <class O, class AI, bool is_db_allowed = true>
struct SelectableAI : public FactoryHolder<AI, O>, public Permissible<O>, public DBPermit
{
    SelectableAI(std::string const& name) : FactoryHolder<AI, O>(name), Permissible<O>(), DBPermit() { }

    bool IsScriptNameAllowedInDB() const final override { return is_db_allowed; }
};


#endif // SelectableAI_h__
