#pragma once

#include <entt.hpp>
#include <named_type.hpp>
#include <rect.hpp>
#include <vector>  // vector

#include "vector2.hpp"

namespace wanderer::comp {
namespace detail {
struct hitbox_entity_t;
}

/**
 * @struct subhitbox
 *
 * @brief Represents a "subhitbox", a member of a `hitbox` instance.
 *
 * @var subhitbox::offset
 * The offset that the subhitbox is positioned at, relative to the origin
 * position. This is useful for updating the position of a `hitbox`.
 * @var subhitbox::rect
 * The actual rectangle that represents the position and size of the subhitbox.
 *
 * @headerfile hitbox.hpp
 */
struct subhitbox final
{
  vector2f offset;
  cen::frect rect;
};

/**
 * @struct hitbox
 *
 * @brief Represents a hitbox that supports multiple subhitboxes.
 *
 * @var hitbox::bounds
 * The bounding area of the hitbox.
 * @var hitbox::boxes
 * The subhitboxes contained in the hitbox.
 *
 * @headerfile hitbox.hpp
 */
struct hitbox final
{
  using entity = fluent::NamedType<entt::entity, detail::hitbox_entity_t>;
  cen::frect bounds;
  std::vector<subhitbox> boxes;
};

}  // namespace wanderer::comp
