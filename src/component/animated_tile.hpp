#pragma once

#include <vector>  // vector

#include "ints.hpp"
#include "milliseconds.hpp"
#include "tile_id.hpp"

namespace wanderer::comp {

/**
 * \struct frame
 *
 * \brief Represents a frame in a tile animation.
 *
 * \var frame::tile
 * The tile ID of the tile that should be rendered when the frame is active.
 * \var frame::duration
 * The duration that the frame should be active, in milliseconds.
 *
 * \headerfile animated_tile.hpp
 */
struct frame final
{
  tile_id tile{glob::emptyTile};
  ms_t duration{};
};

/**
 * \struct animated_tile
 *
 * \brief Represents the animation associated with a tile.
 *
 * \details An animated tile is different than a normal animated entity,
 * since animated tiles can have different durations for each frame.
 * Furthermore, the frames in the animation aren't necessarily "linear", which
 * means that an arbitrary set of tiles in a tileset can make up a tile
 * animation.
 *
 * \var animated_tile::index
 * The current frame index. Starts at 0.
 * \var animated_tile::then
 * The time of the previous update, in milliseconds.
 * \var animated_tile::frames
 * The frames that constitute the animation.
 *
 * \headerfile animated_tile.hpp
 */
struct animated_tile final
{
  int index{0};
  ms_t then{};
  std::vector<frame> frames;
};

template <typename Archive>
void serialize(Archive& archive, frame& f, u32 version)
{
  archive(f.tile, f.duration);
}

template <typename Archive>
void serialize(Archive& archive, animated_tile& a, u32 version)
{
  archive(a.index, a.then, a.frames);
}

}  // namespace wanderer::comp
