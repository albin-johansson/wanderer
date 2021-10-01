#pragma once

#include <entt.hpp>  // entity, null

namespace wanderer::comp {

/// \addtogroup components
/// \{

/// \brief A tag type used to identify humanoids.
struct humanoid final
{};

/// \brief A tag type used to identify the idle state of a humanoid.
struct humanoid_idle final
{};

/// \brief A tag type used to identify the moving state of a humanoid.
struct humanoid_move final
{};

/// \brief Represents the attack state of a humanoid.
struct humanoid_attack final
{
  entt::entity weapon{entt::null};  ///< The weapon used for the attack.
  bool done{};                      ///< Indicates whether or not the attack is done.
};

/// \brief A tag type used to identify the dying state of a humanoid.
struct humanoid_die final
{};

/// \} End of group components

}  // namespace wanderer::comp
