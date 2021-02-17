#pragma once

#include <cen/rect.hpp>
#include <vector>  // vector

#include "entity_type.hpp"
#include "ints.hpp"
#include "vector2.hpp"

namespace wanderer::comp {
namespace detail {
struct hitbox_entity_t;
}

/**
 * \struct subhitbox
 *
 * \brief Represents a "subhitbox", a member of a `hitbox` instance.
 *
 * \var subhitbox::offset
 * The offset that the subhitbox is positioned at, relative to the origin
 * position. This is useful for updating the position of a `hitbox`.
 *
 * \var subhitbox::size
 * The size of the subhitbox.
 *
 * \headerfile hitbox.hpp
 */
struct subhitbox final
{
  vector2f offset;
  cen::farea size;
};

/**
 * \struct hitbox
 *
 * \brief Represents a hitbox that supports multiple subhitboxes.
 *
 * \var hitbox::bounds
 * The bounding area of the hitbox.
 *
 * \var hitbox::boxes
 * The subhitboxes contained in the hitbox.
 *
 * \headerfile hitbox.hpp
 */
struct hitbox final
{
  using entity = entity_type<detail::hitbox_entity_t>;

  vector2f origin;
  cen::frect bounds;
  std::vector<subhitbox> boxes;
  bool enabled{true};
};

template <typename Archive>
void serialization(Archive& archive, subhitbox& sh, u32 version)
{
  archive(sh.offset, sh.size);
}

template <typename Archive>
void serialization(Archive& archive, hitbox& h, u32 version)
{
  archive(h.origin, h.bounds, h.boxes, h.enabled);
}

}  // namespace wanderer::comp
