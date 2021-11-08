#include "fps_system.hpp"

#include <array>        // array
#include <format>       // format_to_n
#include <string_view>  // string_view

#include <centurion.hpp>  // ticks
#include <rune/rune.hpp>  // formatted_string

#include "components/ui/fps_data.hpp"
#include "core/game_constants.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/math/floating.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

void UpdateFps(entt::registry& shared, const float dt)
{
  for (auto&& [entity, data] : shared.view<FpsData>().each()) {
    data.dt = dt;
    data.elapsed = cen::counter::ticks();

    if (data.elapsed >= data.next_update) {
      data.frame = data.elapsed - data.then;
      data.next_update = data.elapsed + data.interval;
    }

    data.then = data.elapsed;
  }
}

void RenderFps(const entt::registry& shared)
{
  auto& graphics = shared.ctx<Ref<GraphicsContext>>().get();

  for (auto&& [entity, data] : shared.view<FpsData>().each()) {
    const auto fps = round(1.0 / (static_cast<double>(data.frame.count()) / 1'000.0));

    {
      const rune::formatted_string<64> str{"Frame: {} ms", data.frame.count()};
      graphics.RenderLabel(str.data(), 12, 6, Anchor::NorthEast);
    }

    {
      const rune::formatted_string<64> str{"FPS: {}", fps};
      graphics.RenderLabel(str.data(), 12, 24, Anchor::NorthEast);
    }
  }
}

}  // namespace wanderer::sys
