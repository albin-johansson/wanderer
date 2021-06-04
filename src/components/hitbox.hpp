#pragma once

#include <array>          // array
#include <centurion.hpp>  // farea, frect
#include <rune.hpp>       // static_vector

#include "core/aliases/entity_type.hpp"
#include "core/aliases/float2.hpp"
#include "core/aliases/ints.hpp"

namespace wanderer::comp {

namespace tags {
struct hitbox_tag;
}  // namespace tags

/// The maximum number of subhitboxes a single hitbox can contain.
inline constexpr usize max_subhitbox_count = 5;

/**
 * \brief Represents a "subhitbox", a member of a `hitbox` instance.
 *
 * \headerfile hitbox.hpp
 */
struct subhitbox final
{
  float2 offset;    ///< Offset relative to the parent hitbox.
  cen::farea size;  ///< The size of the subhitbox.
};

/**
 * \brief Represents a hitbox that supports multiple subhitboxes.
 *
 * \ingroup components
 *
 * \headerfile hitbox.hpp
 */
struct hitbox final
{
  using entity = entity_type<tags::hitbox_tag>;

  float2 origin;      ///< Position of the hitbox
  cen::frect bounds;  ///< Bounding rectangle of all subhitboxes
  rune::static_vector<subhitbox, max_subhitbox_count> boxes;  ///< Associated subhitboxes
  bool enabled{true};  ///< Whether or not the hitbox can collide with other hitboxes
};

void serialize(auto& archive, subhitbox& sh)
{
  archive(sh.offset, sh.size);
}

void serialize(auto& archive, hitbox& h)
{
  archive(h.origin, h.bounds, h.boxes, h.enabled);
}

}  // namespace wanderer::comp
