/**
 * @brief Provides the `Hitbox` component.
 * @file hitbox.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <rect.h>

#include <vector>

#include "wanderer_stdinc.h"

namespace wanderer::component {

/**
 * @struct Hitbox
 * @brief Represents a hitbox that supports multiple subhitboxes.
 *
 * @var Hitbox::bounds
 * The bounding area of the hitbox.
 * @var Hitbox::boxes
 * The subhitboxes contained in the hitbox.
 *
 * @headerfile hitbox.h
 */
struct Hitbox final {
  using entity = fluent::NamedType<entt::entity, struct HitboxEntityTag>;
  ctn::FRect bounds;
  std::vector<ctn::FRect> boxes;
};

}  // namespace wanderer::component
