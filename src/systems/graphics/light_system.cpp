#include "light_system.hpp"

#include <cmath>   // clamp
#include <string>  // string

#include "centurion_utils.hpp"
#include "depth_drawable.hpp"
#include "get_random.hpp"
#include "player.hpp"
#include "point_light.hpp"
#include "resources.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {

inline const auto texture_path = resources::texture("ardentryst/glow.png");

}

void update_lights(entt::registry& registry)
{
  const auto view = registry.view<comp::point_light>();
  view.each([&](comp::point_light& light) {
    light.fluctuation += get_bool() ? light.fluctuationStep : -light.fluctuationStep;

    const auto min = light.size - light.fluctuationLimit;
    const auto max = light.size + light.fluctuationLimit;

    light.fluctuation = std::clamp(light.fluctuation, min, max);
  });
}

void update_player_light_position(entt::registry& registry)
{
  const auto playerEntity = registry.ctx<ctx::player>().entity;
  const auto& drawable = registry.get<comp::depth_drawable>(playerEntity);

  auto& light = registry.get<comp::point_light>(playerEntity);

  const auto center = drawable.dst.center();
  const auto halfSize = (light.size + light.fluctuation) / 2.0f;

  light.position = to_vector(center) - float2{halfSize, halfSize};
}

void render_lights(const entt::registry& registry,
                   const ctx::time_of_day& time,
                   graphics_context& graphics)
{
  auto& texture = graphics.light_canvas();
  texture.set_alpha(time.opacity);

  auto& renderer = graphics.renderer();
  renderer.set_target(&texture);
  renderer.clear_with(cen::colors::black);

  texture.set_blend_mode(cen::blend_mode::blend);
  renderer.fill_with(time.color);

  texture.set_blend_mode(cen::blend_mode::mod);

  constexpr auto source = cen::irect{{}, {80, 80}};
  const auto index = graphics.load("point_light"_hs, texture_path);

  const auto view = registry.view<const comp::point_light>();
  view.each([&](const comp::point_light& light) {
    const auto& pos = light.position;
    const auto size = light.size + light.fluctuation;
    graphics.render(index, source, {pos.x, pos.y, size, size});
  });

  renderer.set_target(nullptr);

  renderer.set_blend_mode(cen::blend_mode::blend);
  renderer.render<int>(texture, {0, 0});
}

void render_light_overlay(const ctx::time_of_day& time, graphics_context& graphics)
{
  const auto opacity = time.opacity;
  graphics.renderer().fill_with(cen::colors::black.with_alpha(opacity));
}

}  // namespace wanderer::sys
