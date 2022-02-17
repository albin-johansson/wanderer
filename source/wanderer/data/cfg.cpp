#include "cfg.hpp"

#include <centurion.hpp>

#include "wanderer/misc/logging.hpp"

namespace wanderer {

auto make_game_cfg() -> game_cfg
{
  // TODO persistent UI scale factor?

  const auto display = cen::display_mode::desktop();

  const auto screenSize = display.size();
  const auto screenRatio =
      static_cast<float32>(screenSize.width) / static_cast<float32>(screenSize.height);

  game_cfg cfg;
  cfg.logical_size_f.x = 960;
  cfg.logical_size_f.y = 960 / screenRatio;

  cfg.logical_size.x = static_cast<int32>(cfg.logical_size_f.x);
  cfg.logical_size.y = static_cast<int32>(cfg.logical_size_f.y);

  debug("Logical size is {}", cfg.logical_size_f);

  cfg.tile_size = {64, 64};
  cfg.humanoid_draw_size = cfg.tile_size * 2.0f;

  return cfg;
}

}  // namespace wanderer
