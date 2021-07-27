#include "light_system.hpp"

#include <cmath>     // clamp
#include <rune.hpp>  // next_bool

#include "components/ctx/viewport.hpp"
#include "components/graphics/depth_drawable.hpp"
#include "components/graphics/point_light.hpp"
#include "components/player.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/resources.hpp"
#include "core/utils/centurion_utils.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {
inline const auto texture_path = resources::texture("ardentryst/glow.png");
}

void update_lights(entt::registry& registry)
{
  for (auto&& [entity, light] : registry.view<comp::point_light>().each())
  {
    light.fluctuation +=
        rune::next_bool() ? light.fluctuation_step : -light.fluctuation_step;

    const auto min = light.size - light.fluctuation_limit;
    const auto max = light.size + light.fluctuation_limit;

    light.fluctuation = std::clamp(light.fluctuation, min, max);
  }
}

void update_player_light_position(entt::registry& registry)
{
  const auto playerEntity = singleton_entity<comp::player>(registry);
  const auto& drawable = registry.get<comp::depth_drawable>(playerEntity);

  auto& light = registry.get<comp::point_light>(playerEntity);
  light.position = to_vector(drawable.dst.center());
}

void render_lights(const entt::registry& registry,
                   graphics_context& graphics,
                   const ctx::time_of_day& time,
                   const ctx::settings& settings)
{
  auto& renderer = graphics.renderer();
  auto& texture = graphics.light_canvas();

  renderer.set_target(texture);
  renderer.clear_with(time.tint);

  const auto index = graphics.load(texture_id{"point_light"_hs}, texture_path);
  const auto& viewport = registry.ctx<ctx::viewport>();
  constexpr auto source = cen::rect(0, 0, 80, 80);

  for (auto&& [entity, light] : registry.view<comp::point_light>().each())
  {
    const auto& pos = light.position;

    const auto size = light.size + light.fluctuation;
    const auto halfSize = size / 2.0f;

    const cen::frect dst{pos.x - halfSize, pos.y - halfSize, size, size};
    if (cen::intersects(viewport.bounds, dst))
    {
      graphics.render(index, source, dst);
    }
  }

  renderer.reset_target();
  renderer.render(texture, cen::point(0, 0));
}

}  // namespace wanderer::sys
