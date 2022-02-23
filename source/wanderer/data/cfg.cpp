#include "cfg.hpp"

#include <centurion.hpp>

#include "wanderer/misc/logging.hpp"
#include "wanderer/core/math.hpp"

namespace wanderer {

auto make_game_cfg() -> game_cfg
{
  // TODO persistent UI scale factor?

  const auto display = cen::display_mode::desktop();
  const auto screen = display.size().as_f();

  debug("Screen size is {}", glm::vec2{screen.width, screen.height});

  game_cfg cfg;
  cfg.logical_size_f.x = 960;
  cfg.logical_size_f.y = cfg.logical_size_f.x * (screen.height / screen.width);

  cfg.logical_size = glmx::as_i(cfg.logical_size_f);

  cfg.tile_size = {48, 48};
  cfg.humanoid_draw_size = cfg.tile_size * 2.0f;

  return cfg;
}

}  // namespace wanderer
