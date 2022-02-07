#include "cfg.hpp"

#include <centurion.hpp>

#include "wanderer/misc/logging.hpp"

namespace wanderer {

auto make_game_cfg() -> game_cfg
{
  const auto display = cen::display_mode::desktop();

  const auto screenSize = display.size();
  const auto screenRatio =
      static_cast<float32>(screenSize.width) / static_cast<float32>(screenSize.height);

  game_cfg cfg;
  cfg.logical_size_f.x = 960;
  cfg.logical_size_f.y = 960 / screenRatio;

  cfg.logical_size.x = static_cast<int32>(cfg.logical_size_f.x);
  cfg.logical_size.y = static_cast<int32>(cfg.logical_size_f.y);

  log_debug("Logical size is ({}, {})", cfg.logical_size_f.x, cfg.logical_size_f.y);

  return cfg;
}

}  // namespace wanderer
