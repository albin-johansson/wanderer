#include "light_system.hpp"

#include <cmath>  // clamp

#include <rune/everything.hpp>  // next_bool

#include "common/ref.hpp"
#include "components/ctx/viewport.hpp"
#include "components/gfx/drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/player.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/resources.hpp"
#include "core/utils/centurion_utils.hpp"

using namespace entt::literals;

namespace wanderer::sys {
namespace {
inline const auto texture_path = resources::texture("ardentryst/glow.png");
}  // namespace

void UpdateLights(entt::registry& registry)
{
  for (auto&& [entity, light] : registry.view<comp::PointLight>().each()) {
    light.fluctuation +=
        rune::next_bool() ? light.fluctuation_step : -light.fluctuation_step;

    const auto min = light.size - light.fluctuation_limit;
    const auto max = light.size + light.fluctuation_limit;

    light.fluctuation = std::clamp(light.fluctuation, min, max);
  }
}

void UpdatePlayerLightPosition(entt::registry& registry)
{
  const auto playerEntity = singleton_entity<comp::Player>(registry);
  const auto& drawable = registry.get<comp::Drawable>(playerEntity);

  auto& light = registry.get<comp::PointLight>(playerEntity);
  light.position = to_vector(drawable.dst.center());
}

void RenderLights(const entt::registry& registry, const ctx::TimeOfDay& time)
{
  auto& graphics = registry.ctx<ref<GraphicsContext>>().get();
  auto& renderer = graphics.get_renderer();
  auto& texture = graphics.light_canvas();

  renderer.set_target(texture);
  renderer.clear_with(time.tint);

  const auto index = graphics.load(texture_id{"point_light"_hs}, texture_path);
  const auto& viewport = registry.ctx<ctx::Viewport>();
  constexpr auto source = cen::rect(0, 0, 80, 80);

  for (auto&& [entity, light] : registry.view<comp::PointLight>().each()) {
    const auto& pos = light.position;

    const auto size = light.size + light.fluctuation;
    const auto halfSize = size / 2.0f;

    const cen::frect dst{pos.x - halfSize, pos.y - halfSize, size, size};
    if (cen::intersects(viewport.bounds, dst)) {
      graphics.render(index, source, dst);
    }
  }

  renderer.reset_target();
  renderer.render(texture, cen::point(0, 0));
}

}  // namespace wanderer::sys
