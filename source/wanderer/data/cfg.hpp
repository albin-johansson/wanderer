#pragma once

#include <glm/glm.hpp>

#include "wanderer/common.hpp"

namespace wanderer {

/**
 * \brief Provides runtime "constants" used by the game.
 */
struct GameConfig final
{
  glm::ivec2 logical_size{};
  glm::vec2 logical_size_f{};
  glm::vec2 tile_size{};
  glm::vec2 humanoid_draw_size{};
};

/**
 * \brief Creates a game configuration appropriate for use on the current system.
 *
 * \return a game configuration.
 */
[[nodiscard]] auto make_game_cfg() -> GameConfig;

}  // namespace wanderer
