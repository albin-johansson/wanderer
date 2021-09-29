#pragma once

#include <vector>  // vector

#include "common/ints.hpp"
#include "common/milliseconds.hpp"
#include "common/tile_id.hpp"
#include "core/game_constants.hpp"

namespace wanderer::comp {

/**
 * \struct frame
 *
 * \brief Represents a frame in a tile animation.
 *
 * \headerfile tile_animation.hpp
 */
struct frame final
{
  tile_id tile{glob::empty_tile};  ///< ID of the tile that should be rendered.
  ms_t duration{};                 ///< The duration that the frame is active.
};

/**
 * \struct tile_animation
 *
 * \brief Represents animations used by tiles.
 *
 * \details An animated tile is different than a normal animated entity,
 * since animated tiles can have different durations for each frame.
 * Furthermore, the frames in the animation aren't necessarily "linear", which
 * means that an arbitrary set of tiles in a tileset can make up a tile
 * animation.
 *
 * \headerfile tile_animation.hpp
 */
struct tile_animation final
{
  uint64 index{0};            ///< Current frame index.
  ms_t then{};                ///< Time of the previous update.
  std::vector<frame> frames;  ///< The frames that constitute the animation.
};

}  // namespace wanderer::comp
