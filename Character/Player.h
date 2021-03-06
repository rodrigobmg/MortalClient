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
#include "../Gameplay/Combat/Attack.h"
#include "../Gameplay/Combat/Skill.h"
#include "../Gameplay/MapleMap/Layer.h"
#include "../Gameplay/MapleMap/MapInfo.h"
#include "../Gameplay/Movement.h"
#include "../Gameplay/Physics/Physics.h"
#include "../Gameplay/Playable.h"
#include "../Util/Randomizer.h"
#include "ActiveBuffs.h"
#include "Buff.h"
#include "Char.h"
#include "CharStats.h"
#include "Inventory/Inventory.h"
#include "Look/CharLook.h"
#include "MonsterBook.h"
#include "PassiveBuffs.h"
#include "QuestLog.h"
#include "SkillBook.h"
#include "TeleRock.h"

#include <unordered_map>

namespace jrc
{
class Player : public Playable, public Char
{
public:
    //! Construct a player object from the given character entry.
    Player(const CharEntry& entry);
    Player();

    //! Draw the player.
    void draw(Layer::Id layer, double viewx, double viewy, float alpha) const;
    //! Overload of `draw` that is inherited from `Char`.
    void draw(double viewx, double viewy, float alpha) const override;
    //! Update the player's animation, physics and states.
    std::int8_t update(const Physics& physics) override;
    //! Set flipped ignore if attacking.
    void set_direction(bool flipped) override;
    //! Set state ignore if attacking.
    void set_state(State stance) override;

    //! Respawn the player at the given position.
    void respawn(Point<std::int16_t> position, bool underwater);
    //! Sends a Keyaction to the player's state, to apply forces, change the
    //! state and other behaviour.
    void send_action(KeyAction::Id action, bool pressed) override;
    //! Recalculates the total stats from base stats, inventories and skills.
    void recalc_stats(bool equip_changed);
    //! Change the equipment at the specified slot and recalculate stats.
    void change_equip(std::int16_t slot);
    //! Use the item from the player's inventory with the given id.
    void use_item(std::int32_t itemid);

    //! Return if the player is attacking.
    bool is_attacking() const;
    //! Return whether the player can attack or not.
    bool can_attack() const;
    //! Return whether the player can use a skill or not.
    SpecialMove::ForbidReason can_use(const SpecialMove& move) const;
    //! Create an attack struct using the player's stats.
    Attack prepare_attack(bool skill) const;

    //! Execute a rush movement.
    void rush(double target_x);

    //! Check whether the player is invincible.
    bool is_invincible() const override;
    //! Handle an attack to the player.
    MobAttackResult damage(const MobAttack& attack);

    //! Apply a buff to the player.
    void give_buff(Buff buff);
    //! Cancel a buff.
    void cancel_buff(Buffstat::Id stat);
    //! Return whether the buff is active.
    bool has_buff(Buffstat::Id stat) const;

    //! Change a skill.
    void change_skill(std::int32_t skill_id,
                      std::int32_t level,
                      std::int32_t master_level,
                      std::int64_t expiration);
    //! Put a skill on cooldown.
    void add_cooldown(std::int32_t skill_id, std::int32_t cool_time);
    //! Check if a skill is on cooldown.
    bool has_cooldown(std::int32_t skill_id) const;

    //! Change the player's level, display the levelup effect.
    void change_level(std::uint16_t level);
    //! Change the player's job, display the job change effect.
    void change_job(std::uint16_t job_id);

    //! Return the character's level.
    std::uint16_t get_level() const override;
    //! Return the character's level of a skill.
    std::int32_t get_skill_level(std::int32_t skill_id) const override;
    //! Return the character's attacking speed.
    std::int8_t get_integer_attack_speed() const override;

    //! Returns the current walking force, calculated from the total ES_SPEED
    //! stat.
    float get_walk_force() const;
    //! Returns the current jumping force, calculated from the total ES_JUMP
    //! stat.
    float get_jump_force() const;
    //! Returns the climbing force, calculated from the total ES_SPEED stat.
    float get_climb_force() const;
    //! Returns the flying force.
    float get_fly_force() const;

    //! Return whether the player is underwater.
    bool is_underwater() const;
    //! Returns if a Keyaction is currently active.
    bool is_key_down(KeyAction::Id action) const;
    //! Return a pointer to the ladder the player is on.
    nullable_ptr<const Ladder> get_ladder() const;

    //! Set player's stats.
    void set_stats(const StatsEntry& entry) noexcept;
    //! Change player's position to the seat's position and stance to
    //! Char::SIT.
    void set_seat(nullable_ptr<const Seat> seat);
    //! Change player's x-pos to the ladder x and change stance to Char::LADDER
    //! or Char::ROPE.
    void set_ladder(nullable_ptr<const Ladder> ladder);

    //! Obtain a reference to the player's stats.
    CharStats& get_stats();
    //! Obtain a const reference to the player's stats.
    const CharStats& get_stats() const;
    //! Obtain a reference to the player's inventory.
    Inventory& get_inventory();
    //! Obtain a const reference to the player's inventory.
    const Inventory& get_inventory() const;
    //! Obtain a reference to the player's skills.
    Skillbook& get_skills();
    //! Obtain a reference to the player's questlog.
    Questlog& get_quests();
    //! Obtain a reference to the player's telerock locations.
    Telerock& get_telerock();
    //! Obtain a reference to the player's monsterbook.
    Monsterbook& get_monsterbook();

private:
    CharStats stats;
    Inventory inventory;
    Skillbook skillbook;
    Questlog questlog;
    Telerock telerock;
    Monsterbook monsterbook;

    EnumMap<Buffstat::Id, Buff> buffs;
    ActiveBuffs active_buffs;
    PassiveBuffs passive_buffs;

    std::unordered_map<std::int32_t, std::int32_t> cooldowns;

    std::unordered_map<KeyAction::Id, bool> keys_down;

    Movement last_move;

    nullable_ptr<const Ladder> ladder;
    bool underwater;
};
} // namespace jrc
