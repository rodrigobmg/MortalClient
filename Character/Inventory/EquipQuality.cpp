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
#include "EquipQuality.h"

#include "../../Data/EquipData.h"

namespace jrc
{
EquipQuality::Id
EquipQuality::check_quality(std::int32_t item_id,
                            bool scrolled,
                            const EnumMap<Equipstat::Id, std::uint16_t>& stats)
{
    const EquipData& data = EquipData::get(item_id);

    std::int16_t delta = 0;
    for (auto iter : stats) {
        Equipstat::Id es = iter.first;
        std::uint16_t stat = iter.second;
        std::uint16_t defstat = data.get_def_stat(es);
        delta += stat - defstat;
    }

    if (delta < -5) {
        return scrolled ? ORANGE : GREY;
    } else if (delta < 7) {
        return scrolled ? ORANGE : WHITE;
    } else if (delta < 14) {
        return BLUE;
    } else if (delta < 21) {
        return VIOLET;
    } else {
        return GOLD;
    }
}
} // namespace jrc
