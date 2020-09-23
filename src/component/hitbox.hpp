/**
 * @brief Provides the `Hitbox` component.
 * @file hitbox.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <rect.hpp>
#include <vector>

#include "vector_2.hpp"
#include "wanderer_stdinc.hpp"

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
 * @headerfile hitbox.hpp
 */
struct Subhitbox final {
  vector2f offset;
  cen::frect rect;
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
 * @headerfile hitbox.hpp
 */
struct Hitbox final {
  using entity = fluent::NamedType<entt::entity, struct HitboxEntityTag>;
  cen::frect bounds;
  std::vector<Subhitbox> boxes;
};

}  // namespace wanderer::comp
