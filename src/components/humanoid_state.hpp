#pragma once

#include <entt.hpp>

#include "direction.hpp"
#include "ints.hpp"

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
  bool done{false};
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

template <typename Archive>
void serialize(Archive&, humanoid&, u32 version)
{}

template <typename Archive>
void serialize(Archive&, humanoid_idle&, u32 version)
{}

template <typename Archive>
void serialize(Archive&, humanoid_move&, u32 version)
{}

template <typename Archive>
void serialize(Archive& archive, humanoid_attack& ha, u32 version)
{
  archive(ha.weapon, ha.done);
}

template <typename Archive>
void serialize(Archive&, humanoid_die&, u32 version)
{}

}  // namespace wanderer::comp
