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
#include "../../Graphics/Texture.h"
#include "../../Template/Point.h"
#include "nlnx/node.hpp"

#include <cstdint>
#include <string>
#include <string_view>

namespace jrc
{
//! Represents a tile on a map.
class Tile
{
public:
    Tile(nl::node src, std::string_view tileset);

    //! Draw the tile.
    void draw(Point<std::int16_t> viewpos) const;
    //! Returns depth of the tile.
    std::uint8_t get_z() const;

private:
    Texture texture;
    Point<std::int16_t> pos;
    std::uint8_t z;
};
} // namespace jrc
