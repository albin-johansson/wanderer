#include "render_movables_system.h"

#include "animated.h"
#include "drawable.h"
#include "game_constants.h"
#include "movable.h"

using namespace centurion;

namespace wanderer::system {

inline constexpr FArea entitySize{g_entityDrawWidth, g_entityDrawHeight};

void render_movables(entt::registry& registry, Renderer& renderer)
{
  const auto entities = registry.view<Movable, Drawable>();
  for (const auto entity : entities) {
    const auto& movable = entities.get<Movable>(entity);
    const auto& drawable = entities.get<Drawable>(entity);

    const auto [x, y] = movable.interpolatedPos;
    const IRect src{{drawable.srcX, drawable.srcY}, {64, 64}};
    const FRect dst{{x, y}, entitySize};

    renderer.render_tf(*drawable.texture, src, dst);
  }
}

}  // namespace wanderer::system
