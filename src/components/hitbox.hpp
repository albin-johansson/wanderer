#pragma once

#include <centurion.hpp>  // farea, frect
#include <vector>         // vector

#include "core/aliases/entity_type.hpp"
#include "core/aliases/float2.hpp"
#include "core/aliases/ints.hpp"

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
 * \headerfile hitbox.hpp
 */
struct subhitbox final
{
  float2 offset;    ///< Offset relative to the parent hitbox.
  cen::farea size;  ///< The size of the subhitbox.
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

  float2 origin;
  cen::frect bounds;
  std::vector<subhitbox> boxes;
  bool enabled{true};
};

void serialize(auto& archive, subhitbox& sh, u32 version)
{
  archive(sh.offset, sh.size);
}

void serialize(auto& archive, hitbox& h, u32 version)
{
  archive(h.origin, h.bounds, h.boxes, h.enabled);
}

}  // namespace wanderer::comp
