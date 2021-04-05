#include "game_constants.hpp"
#include "viewport_system.hpp"

namespace wanderer::sys {

auto make_viewport(const cen::farea& levelSize) noexcept -> ctx::viewport
{
  ctx::viewport viewport;

  viewport.bounds = {{}, glob::logical_size<cen::farea>};
  viewport.levelSize = levelSize;

  return viewport;
}

}  // namespace wanderer::sys
