#pragma once

#include <centurion.hpp>  // farea, frect
#include <rune/rune.hpp>  // static_vector

#include "wanderer_std.hpp"

namespace wanderer {

/// The maximum number of subhitboxes a single hitbox can contain.
constexpr usize max_subhitbox_count = 5;

/// \brief Represents a "subhitbox", a member of a `hitbox` instance.
/// \ingroup components
struct Subhitbox final
{
  float2 offset{};  ///< Offset relative to the parent hitbox.
  cen::farea size;  ///< The size of the subhitbox.
};

/// \brief Represents a hitbox that supports multiple subhitboxes.
/// \ingroup components
struct Hitbox final
{
  using hitbox_vector = rune::static_vector<Subhitbox, max_subhitbox_count>;

  float2 origin{};      ///< Position of the hitbox.
  cen::frect bounds;    ///< Bounding rectangle of all subhitboxes.
  hitbox_vector boxes;  ///< Associated subhitboxes.
  bool enabled{true};   ///< Whether or not the hitbox can collide with other hitboxes.
};

}  // namespace wanderer
