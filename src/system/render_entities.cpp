#include "render_entities.h"

#include "animated.h"
#include "drawable.h"
#include "game_constants.h"
#include "movable.h"

using namespace centurion;

namespace wanderer {

inline constexpr FArea entitySize{g_entityDrawWidth, g_entityDrawHeight};

void render_entities(entt::registry& registry, Renderer& renderer)
{
  const auto entities = registry.view<Movable, Animated, Drawable>();
  for (const auto entity : entities) {
    const auto& movable = entities.get<Movable>(entity);
    const auto& animated = entities.get<Animated>(entity);
    const auto& drawable = entities.get<Drawable>(entity);

    const auto srcX = movable.velocity.is_zero() ? 0 : animated.frame * 64;

    const auto [x, y] = movable.interpolatedPos;
    const IRect src{{static_cast<int>(srcX), drawable.srcY}, {64, 64}};
    const FRect dst{{x, y}, entitySize};

    renderer.render_tf(*drawable.texture, src, dst);
  }
}

}  // namespace wanderer
