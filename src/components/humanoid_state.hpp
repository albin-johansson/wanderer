#pragma once

#include <entt.hpp>  // entity

#include "core/aliases/ints.hpp"
#include "core/direction.hpp"

namespace wanderer::comp {

/**
 * \struct humanoid
 *
 * \brief A tag type used to identify humanoids.
 *
 * \headerfile humanoid_state.hpp
 */
struct humanoid final
{};

/**
 * \struct humanoid_idle
 *
 * \brief A tag type used to identify the idle state of a humanoid.
 *
 * \headerfile humanoid_state.hpp
 */
struct humanoid_idle final
{};

/**
 * \struct humanoid_move
 *
 * \brief A tag type used to identify the moving state of a humanoid.
 *
 * \headerfile humanoid_state.hpp
 */
struct humanoid_move final
{};

/**
 * \struct humanoid_attack
 *
 * \brief Represents the attack state of a humanoid.
 *
 * \var humanoid_attack::weapon
 * The weapon used for the attack.
 * \var humanoid_attack::done
 * Indicates whether or not the attack is done.
 *
 * \headerfile humanoid_state.hpp
 */
struct humanoid_attack final
{
  entt::entity weapon{entt::null};  // TODO weapon component entity tag
  bool done{};
};

/**
 * \struct humanoid_die
 *
 * \brief A tag type used to identify the dying state of a humanoid.
 *
 * \headerfile humanoid_state.hpp
 */
struct humanoid_die final
{};

void serialize(auto&, humanoid&, u32 version)
{}

void serialize(auto&, humanoid_idle&, u32 version)
{}

void serialize(auto&, humanoid_move&, u32 version)
{}

void serialize(auto& archive, humanoid_attack& ha, u32 version)
{
  archive(ha.weapon, ha.done);
}

void serialize(auto&, humanoid_die&, u32 version)
{}

}  // namespace wanderer::comp
