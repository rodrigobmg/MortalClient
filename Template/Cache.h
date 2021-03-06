//////////////////////////////////////////////////////////////////////////////
// This file is part of the LibreMaple MMORPG client                        //
// Copyright © 2015-2016 Daniel Allendorf, 2018-2019 LibreMaple Team        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <https://www.gnu.org/licenses/>.   //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include <cstdint>
#include <unordered_map>

namespace jrc
{
template<typename T>
//! Template for a cache of game objects which can be constructed from an
//! identifier.
//!
//! The `get()` factory method is `static`.
class Cache
{
public:
    virtual ~Cache() = default;

    //! Return a reference to the game object with the specified ID.
    //!
    //! If the object is not in cache, it is created.
    static const T& get(std::int32_t id)
    {
        auto iter = cache.find(id);
        if (iter == cache.end()) {
            iter = cache.emplace(id, T{id}).first;
        }
        return iter->second;
    }

private:
    static std::unordered_map<std::int32_t, T> cache;
};

template<typename T>
std::unordered_map<std::int32_t, T> Cache<T>::cache;
} // namespace jrc
