#pragma once

#include <vector>  // vector

#include "core/aliases/ints.hpp"
#include "core/aliases/milliseconds.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::comp {

/**
 * \struct frame
 *
 * \brief Represents a frame in a tile animation.
 *
 * \headerfile animated_tile.hpp
 */
struct frame final
{
  tile_id tile{glob::empty_tile};  ///< ID of the tile that should be rendered.
  ms_t duration{};                 ///< The duration that the frame is active.
};

void serialize(auto& archive, frame& f, u32 version)
{
  archive(f.tile, f.duration);
}

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
 * \headerfile animated_tile.hpp
 */
struct animated_tile final  // TODO rename to tile_animation?
{
  int index{0};               ///< Current frame index.
  ms_t then{};                ///< Time of the previous update.
  std::vector<frame> frames;  ///< The frames that constitute the animation.
};

void serialize(auto& archive, animated_tile& a, u32 version)
{
  archive(a.index, a.then, a.frames);
}

}  // namespace wanderer::comp
