#include "cfg.hpp"

#include <centurion.hpp>

#include "wanderer/misc/logging.hpp"

namespace wanderer {

auto make_game_cfg() -> game_cfg
{
  // TODO persistent UI scale factor?

  const auto display = cen::display_mode::desktop();
  const auto screen = display.size().as_f();

  game_cfg cfg;
  cfg.logical_size_f.x = 1200;
  cfg.logical_size_f.y = cfg.logical_size_f.x * (screen.height / screen.width);

  cfg.logical_size.x = static_cast<int32>(cfg.logical_size_f.x);
  cfg.logical_size.y = static_cast<int32>(cfg.logical_size_f.y);

  debug("Logical size is {}", cfg.logical_size_f);

  cfg.tile_size = {64, 64};
  cfg.humanoid_draw_size = cfg.tile_size * 2.0f;

  return cfg;
}

}  // namespace wanderer
