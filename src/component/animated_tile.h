/**
 * @brief Provides the `AnimatedTile` component.
 * @file animated_tile.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <vector>

#include "wanderer_stdinc.h"

namespace wanderer::component {

/**
 * @struct Frame
 * @brief Represents a frame in a tile animation.
 *
 * @var Frame::tile
 * The tile ID of the tile that should be rendered when the frame is active.
 * @var Frame::duration
 * The duration that the frame should be active, in milliseconds.
 *
 * @headerfile animated_tile.h
 */
struct Frame final {
  TileID tile{g_emptyTile};
  u32 duration{};
};

/**
 * @struct AnimatedTile
 * @brief Represents the animation associated with a tile.
 *
 * @details An animated tile is different than a normal animated entity,
 * since animated tiles can have different durations for each frame.
 * Furthermore, the frames in the animation aren't necessarily "linear", which
 * means that an arbitrary set of tiles in a tileset can make up a tile
 * animation.
 *
 * @var AnimatedTile::frame
 * The current frame index. Starts at 0.
 * @var AnimatedTile::then
 * The time of the previous update, in milliseconds.
 * @var AnimatedTile::frames
 * The frames that constitute the animation.
 *
 * @headerfile animated_tile.h
 */
struct AnimatedTile final {
  u32 frame{0};
  u32 then{};
  std::vector<Frame> frames;
};

}  // namespace wanderer::component
