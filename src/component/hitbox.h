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

#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace wanderer::comp {

/**
 * @struct Subhitbox
 * @brief Represents a "subhitbox", a member of a `Hitbox` instance.
 *
 * @var Subhitbox::offset
 * The offset that the subhitbox is positioned at, relative to the origin
 * position. This is useful for updating the position of a `Hitbox`.
 * @var Subhitbox::rect
 * The actual rectangle that represents the position and size of the subhitbox.
 *
 * @headerfile hitbox.h
 */
struct Subhitbox final {
  vector2f offset;
  ctn::FRect rect;
};

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
  std::vector<Subhitbox> boxes;
};

}  // namespace wanderer::comp
