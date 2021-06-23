#include "fps_system.hpp"

#include <centurion.hpp>  // ticks
#include <format>         // format

#include "components/ui/fps_data.hpp"
#include "core/game_constants.hpp"
#include "core/math/floating.hpp"

namespace wanderer::sys {

void update_fps(entt::registry& shared, const rune::delta_time dt)
{
  for (auto&& [entity, data] : shared.view<comp::fps_data>().each())
  {
    data.dt = dt;
    data.elapsed = cen::counter::ticks();

    if (data.elapsed >= data.next_update)
    {
      data.frame = data.elapsed - data.then;
      data.next_update = data.elapsed + data.interval;
    }

    data.then = data.elapsed;
  }
}

void render_fps(const entt::registry& shared, graphics_context& graphics)
{
  for (auto&& [entity, data] : shared.view<comp::fps_data>().each())
  {
    const auto fps = round(1.0 / (static_cast<double>(data.frame.count()) / 1'000.0));

    graphics.render_outlined_text(std::format("Frame: {} ms", data.frame.count()),
                                  cen::point(glob::logical_width<int> - 125, 6));
    graphics.render_outlined_text(std::format("FPS: {}", fps),
                                  cen::point(glob::logical_width<int> - 55, 6));
  }
}

}  // namespace wanderer::sys
