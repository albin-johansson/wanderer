#pragma once

#include <centurion.hpp>  // farea, frect

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"

namespace wanderer::ctx {

/**
 * \struct viewport
 * \brief Represents an area that is visible for the player.
 *
 * \var viewport::bounds
 * The position and size of the viewport.
 *
 * \var viewport::levelSize
 * The size of the level that the viewport is associated with.
 *
 * \var viewport::keepInBounds
 * Indicates whether or not the viewport is allowed to be positioned in a way
 * so that the area outside of the level is displayed. This is usually
 * disabled for small levels (e.g. houses) and enabled for the world levels.
 *
 * \headerfile viewport.hpp
 */
struct viewport final
{
  cen::frect bounds;
  cen::farea levelSize;
  bool keepInBounds{};
};

void serialize(auto& archive, viewport& v, u32 version)
{
  archive(v.bounds, v.levelSize, v.keepInBounds);
}

}  // namespace wanderer::ctx
