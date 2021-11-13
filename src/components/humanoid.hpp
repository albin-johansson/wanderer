#pragma once

#include <entt/entt.hpp>  // entity, null

namespace wanderer {

/// \addtogroup components
/// \{

/// \brief A tag type used to identify humanoids.
struct Humanoid final
{};

/// \brief A tag type used to identify the idle state of a humanoid.
struct HumanoidIdle final
{};

/// \brief A tag type used to identify the moving state of a humanoid.
struct HumanoidMove final
{};

/// \brief Represents the attack state of a humanoid.
struct HumanoidAttack final
{
  entt::entity weapon{entt::null};  ///< The weapon used for the attack.
  bool done{};                      ///< Indicates whether or not the attack is done.
};

/// \brief A tag type used to identify the dying state of a humanoid.
struct HumanoidDie final
{};

/// \} End of group components

}  // namespace wanderer
