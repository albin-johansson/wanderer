#pragma once

#include <vector>  // vector

#include "core/game_constants.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

/// \brief Represents a frame in a tile animation.
/// \ingroup components
struct Frame final
{
  TileID tile{glob::empty_tile};  ///< ID of the tile that should be rendered.
  ms_t duration{};                ///< The duration that the frame is active.
};

/**
 * \brief Represents animations used by tiles.
 *
 * \details An animated tile is different than a normal animated entity, since animated
 * tiles can have different durations for each frame. Furthermore, the frames in the
 * animation aren't necessarily "linear", which means that an arbitrary set of tiles in
 * a tileset can make up a tile animation.
 *
 * \ingroup components
 */
struct TileAnimation final
{
  uint64 index{0};            ///< Current frame index.
  ms_t then{};                ///< Time of the previous update.
  std::vector<Frame> frames;  ///< The frames that constitute the animation.
};

}  // namespace wanderer
