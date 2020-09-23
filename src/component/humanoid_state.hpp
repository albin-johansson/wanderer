/**
 * @brief Provides components that represent the various humanoid states.
 * @file humanoid_state.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include "direction.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct Humanoid
 * @brief A tag type used to identify humanoids.
 * @headerfile humanoid_state.hpp
 */
struct Humanoid final {
};

/**
 * @struct HumanoidIdle
 * @brief A tag type used to identify the idle state of a humanoid.
 * @headerfile humanoid_state.hpp
 */
struct HumanoidIdle final {
};

/**
 * @struct HumanoidMove
 * @brief A tag type used to identify the moving state of a humanoid.
 * @headerfile humanoid_state.hpp
 */
struct HumanoidMove final {
};

/**
 * @struct HumanoidAttack
 * @brief Represents the attack state of a humanoid.
 *
 * @var HumanoidAttack::weapon
 * The weapon used for the attack.
 * @var HumanoidAttack::done
 * Indicates whether or not the attack is done.
 *
 * @headerfile humanoid_state.hpp
 */
struct HumanoidAttack final {
  entt::entity weapon{entt::null};  // TODO weapon component entity tag
  bool done{false};
};

/**
 * @struct HumanoidDie
 * @brief A tag type used to identify the dying state of a humanoid.
 * @headerfile humanoid_state.hpp
 */
struct HumanoidDie final {
};

}  // namespace wanderer::comp
