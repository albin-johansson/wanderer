#include "light_system.hpp"

#include <cmath>   // clamp
#include <string>  // string

#include "components/graphics/depth_drawable.hpp"
#include "components/graphics/point_light.hpp"
#include "core/centurion_utils.hpp"
#include "core/math/get_random.hpp"
#include "core/resources/resources.hpp"
#include "ctx/player.hpp"
#include "ctx/viewport.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline const auto texture_path = resources::texture("ardentryst/glow.png");

}

void update_lights(entt::registry& registry)
{
  for (auto&& [entity, light] : registry.view<comp::point_light>().each())
  {
    light.fluctuation += next_bool() ? light.fluctuationStep : -light.fluctuationStep;

    const auto min = light.size - light.fluctuationLimit;
    const auto max = light.size + light.fluctuationLimit;

    light.fluctuation = std::clamp(light.fluctuation, min, max);
  }
}

void update_player_light_position(entt::registry& registry)
{
  const auto playerEntity = registry.ctx<ctx::player>().entity;
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

  if (settings.simulateLights)
  {
    auto& texture = graphics.light_canvas();
    texture.set_alpha(time.opacity);

    renderer.set_target(&texture);
    renderer.clear_with(cen::colors::black);

    texture.set_blend_mode(cen::blend_mode::blend);
    renderer.fill_with(time.color);

    texture.set_blend_mode(cen::blend_mode::mod);

    const auto index = graphics.load("point_light"_hs, texture_path);
    const auto& viewport = registry.ctx<const ctx::viewport>();

    constexpr cen::irect source{{}, {80, 80}};

    for (auto&& [entity, light] : registry.view<const comp::point_light>().each())
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

    renderer.set_target(nullptr);
    renderer.set_blend_mode(cen::blend_mode::blend);
    renderer.render<int>(texture, {0, 0});
  }
  else
  {
    renderer.fill_with(cen::colors::black.with_alpha(time.opacity));
  }
}

}  // namespace wanderer::sys
