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

#ifndef FIRELANDS_MEMORY_H
#define FIRELANDS_MEMORY_H

#include <memory>

namespace Firelands
{
namespace Impl
{
template<typename T, typename Del>
struct unique_ptr_deleter
{
    using pointer = T;
    unique_ptr_deleter(Del deleter) : _deleter(std::move(deleter)) { }

    void operator()(pointer ptr) const { _deleter(ptr); }

private:
    Del _deleter;
};
}

template<typename T, typename Del>
auto make_unique_ptr_with_deleter(T ptr, Del&& deleter)
{
    using Deleter_t = Impl::unique_ptr_deleter<T, Del>;

    return std::unique_ptr<T, Deleter_t>(ptr, Deleter_t(std::forward<Del>(deleter)));
}
}

#endif // FIRELANDS_MEMORY_H
