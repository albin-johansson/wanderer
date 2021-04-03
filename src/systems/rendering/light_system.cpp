#include "light_system.hpp"

#include <cmath>  // clamp

#include "centurion_utils.hpp"
#include "depth_drawable.hpp"
#include "get_random.hpp"
#include "menu_constants.hpp"
#include "player.hpp"
#include "point_light.hpp"

namespace wanderer::sys {

void update_lights(entt::registry& registry)
{
  const auto view = registry.view<comp::point_light>();
  view.each([&](comp::point_light& light) {
    light.fluctuation += get_bool() ? -0.5f : 0.5f;

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
  auto& renderer = graphics.renderer();

  using namespace entt::literals;
  const auto index =
      graphics.load("point_light"_hs, "resources/images/Ardentryst/glow.png");

  // TODO see if this texture can be reused
  cen::texture texture{renderer,
                       graphics.pixel_format(),
                       cen::texture_access::target,
                       glob::logical_size<>};
  texture.set_alpha(time.opacity);

  renderer.set_target(&texture);

  // Render transparent rectangle over entire viewport
  texture.set_blend_mode(cen::blend_mode::blend);
  renderer.set_color(time.color);
  renderer.fill();

  // Prepare texture for light rendering
  texture.set_blend_mode(cen::blend_mode::mod);

  constexpr auto source = cen::irect{{}, {80, 80}};
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

}  // namespace wanderer::sys
