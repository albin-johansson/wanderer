#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

/// A tag type used to identify humanoids.
struct humanoid final
{};

/// A tag type used to identify the idle state of a humanoid.
struct humanoid_idle final
{};

/// A tag type used to identify the moving state of a humanoid.
struct humanoid_move final
{};

/// Represents the attack state of a humanoid.
struct humanoid_attack final
{
  entt::entity weapon{entt::null};  ///< The weapon used for the attack.
  bool done{};                      ///< Indicates whether or not the attack is done.
};

/// A tag type used to identify the dying state of a humanoid.
struct humanoid_die final
{};

}  // namespace wanderer::comp
