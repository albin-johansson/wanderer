#include "rendering_system.hpp"

#include <tuple>  // tie

#include "wanderer/core/centurion_utils.hpp"
#include "wanderer/core/graphics.hpp"
#include "wanderer/data/components/rendering.hpp"
#include "wanderer/data/components/world.hpp"
#include "wanderer/misc/exception.hpp"

namespace wanderer::sys {

void sort_drawables(entt::registry& registry, const sort_strategy strategy)
{
  auto sorter = [&](const entt::entity a, const entt::entity b) {
    const auto& lhsDrawable = registry.get<comp::drawable>(a);
    const auto& rhsDrawable = registry.get<comp::drawable>(b);

    const auto& lhsObject = registry.get<comp::game_object>(a);
    const auto& rhsObject = registry.get<comp::game_object>(b);

    const auto lhsCenterY = lhsObject.position.y + (lhsObject.size.y / 2.0f);
    const auto rhsCenterY = rhsObject.position.y + (rhsObject.size.y / 2.0f);

    return std::tie(lhsDrawable.layer_index, lhsDrawable.depth_index, lhsCenterY) <
           std::tie(rhsDrawable.layer_index, rhsDrawable.depth_index, rhsCenterY);
  };

  switch (strategy) {
    case sort_strategy::std:
      registry.sort<comp::drawable>(sorter, entt::std_sort{});
      break;

    case sort_strategy::insertion:
      registry.sort<comp::drawable>(sorter, entt::insertion_sort{});
      break;

    default:
      throw_traced(wanderer_error{"Invalid sort strategy!"});
  }
}

void render_drawables(const entt::registry& registry, graphics_ctx& graphics)
{
  const auto& viewport = registry.ctx<comp::viewport>();
  const auto viewportRect = as_rect(viewport.offset, viewport.size);

  for (auto&& [entity, drawable] : registry.view<comp::drawable>().each()) {
    const auto& object = registry.get<comp::game_object>(entity);
    cen::frect dest{object.position.x, object.position.y, object.size.x, object.size.y};

    if (cen::intersects(viewportRect, dest)) {
      dest.offset_x(-viewport.offset.x);
      dest.offset_y(-viewport.offset.y);
      graphics.render_texture(drawable.texture, drawable.src, dest);
    }
  }
}

}  // namespace wanderer::sys