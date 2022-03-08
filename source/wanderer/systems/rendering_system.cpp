#include "rendering_system.hpp"

#include <algorithm>  // clamp
#include <tuple>      // tie

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/core/random.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/misc/exception.hpp"

namespace wanderer::sys {

void sort_drawables(entt::registry& registry, const sort_strategy strategy)
{
  auto sorter = [&](const entt::entity a, const entt::entity b) {
    const auto& lhsDrawable = registry.get<comp::Drawable>(a);
    const auto& rhsDrawable = registry.get<comp::Drawable>(b);

    const auto& lhsObject = registry.get<comp::GameObject>(a);
    const auto& rhsObject = registry.get<comp::GameObject>(b);

    const auto lhsCenterY = lhsObject.position.y + (lhsObject.size.y / 2.0f);
    const auto rhsCenterY = rhsObject.position.y + (rhsObject.size.y / 2.0f);

    return std::tie(lhsDrawable.layer_index, lhsDrawable.depth_index, lhsCenterY) <
           std::tie(rhsDrawable.layer_index, rhsDrawable.depth_index, rhsCenterY);
  };

  switch (strategy) {
    case sort_strategy::std:
      registry.sort<comp::Drawable>(sorter, entt::std_sort{});
      break;

    case sort_strategy::insertion:
      registry.sort<comp::Drawable>(sorter, entt::insertion_sort{});
      break;

    default:
      throw_traced(wanderer_error{"Invalid sort strategy!"});
  }
}

void update_lights(entt::registry& registry)
{
  for (auto&& [entity, light] : registry.view<comp::PointLight>().each()) {
    light.fluctuation += next_bool() ? light.step_size : -light.step_size;

    const auto min = light.size - light.limit;
    const auto max = light.size + light.limit;

    light.fluctuation = std::clamp(light.fluctuation, min, max);
  }
}

void render_drawables(const entt::registry& registry, graphics_ctx& graphics)
{
  const auto& viewport = registry.ctx<comp::Viewport>();
  const auto viewportRect = as_rect(viewport.offset, viewport.size);

  for (auto&& [entity, drawable] : registry.view<comp::Drawable>().each()) {
    const auto& object = registry.get<comp::GameObject>(entity);
    cen::frect dest{object.position.x, object.position.y, object.size.x, object.size.y};

    if (cen::intersects(viewportRect, dest)) {
      dest.offset_x(-viewport.offset.x);
      dest.offset_y(-viewport.offset.y);
      graphics.render_texture(drawable.texture, drawable.src, dest);
    }
  }
}

void render_lights(const entt::registry& registry, graphics_ctx& graphics)
{
  const auto& viewport = registry.ctx<comp::Viewport>();
  const auto viewportRect = as_rect(viewport.offset, viewport.size);

  auto& renderer = graphics.renderer();
  auto& canvas = graphics.get_light_canvas();

  const auto& date = registry.ctx<comp::DateAndTime>();
  renderer.set_target(canvas);
  renderer.clear_with(date.tint);

  for (auto&& [entity, object, light] :
       registry.view<comp::GameObject, comp::PointLight>().each()) {
    const auto pos = object.position + light.offset;
    const auto size = light.size + light.fluctuation;

    const auto halfSize = size / 2.0f;
    cen::frect dest{pos.x - halfSize, pos.y - halfSize, size, size};

    if (cen::intersects(viewportRect, dest)) {
      dest.offset_x(-viewport.offset.x);
      dest.offset_y(-viewport.offset.y);
      graphics.render_light(dest);
    }
  }

  renderer.reset_target();
  renderer.render(canvas, cen::ipoint{0, 0});
}

}  // namespace wanderer::sys