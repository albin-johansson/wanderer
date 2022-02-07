#pragma once

#include <glm/glm.hpp>

#include "wanderer/common.hpp"

namespace wanderer {

/**
 * \brief Provides runtime "constants" used by the game.
 */
struct game_cfg final
{
  glm::ivec2 logical_size{};
  glm::fvec2 logical_size_f{};
};

/**
 * \brief Creates a game configuration appropriate for use on the current system.
 *
 * \return a game configuration.
 */
[[nodiscard]] auto make_game_cfg() -> game_cfg;

}  // namespace wanderer
