#include "fps_system.hpp"

#include <array>                // array
#include <centurion.hpp>        // ticks
#include <format>               // format_to_n
#include <rune/everything.hpp>  // formatted_string
#include <string_view>          // string_view

#include "common/ref.hpp"
#include "components/ui/fps_data.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/math/floating.hpp"

namespace wanderer::sys {

void update_fps(entt::registry& shared, const float dt)
{
  for (auto&& [entity, data] : shared.view<comp::fps_data>().each()) {
    data.dt = dt;
    data.elapsed = cen::counter::ticks();

    if (data.elapsed >= data.next_update) {
      data.frame = data.elapsed - data.then;
      data.next_update = data.elapsed + data.interval;
    }

    data.then = data.elapsed;
  }
}

void render_fps(const entt::registry& shared)
{
  auto& graphics = shared.ctx<ref<graphics_context>>().get();

  for (auto&& [entity, data] : shared.view<comp::fps_data>().each()) {
    const auto fps = round(1.0 / (static_cast<double>(data.frame.count()) / 1'000.0));

    {
      const rune::formatted_string<64> str{"Frame: {} ms", data.frame.count()};
      graphics.render_outlined_text(str.view(),
                                    cen::point(glob::logical_width<int> - 125, 6));
    }

    {
      const rune::formatted_string<64> str{"FPS: {}", fps};
      graphics.render_outlined_text(str.view(),
                                    cen::point(glob::logical_width<int> - 55, 6));
    }
  }
}

}  // namespace wanderer::sys
