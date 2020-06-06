#include "humanoid_animation_system.h"

#include "animated.h"
#include "drawable.h"
#include "entity_state.h"
#include "movable.h"

namespace wanderer {
namespace {

inline constexpr int idleSourceY = 512;  // yes these are the same
inline constexpr int moveSourceY = 512;

template <typename Lambda>
void update(entt::registry& registry, entt::entity entity, Lambda&& lambda)
{
  if (auto* animated = registry.try_get<Animated>(entity); animated) {
    if (auto* movable = registry.try_get<Movable>(entity); movable) {
      if (auto* drawable = registry.try_get<Drawable>(entity); drawable) {
        lambda(*animated, *movable, *drawable);
      }
    }
  }
}

int source_y(int y, Direction direction) noexcept
{
  switch (direction) {
    default:
      [[fallthrough]];
    case Direction::Up:
      return y;
    case Direction::Left:
      return y + 64;
    case Direction::Down:
      return y + 128;
    case Direction::Right:
      return y + 192;
  }
}

}  // namespace

void enter_idle(entt::registry& registry, entt::entity entity)
{
  update(registry,
         entity,
         [](Animated& animated, Movable& movable, Drawable& drawable) noexcept {
           animated.frame = 0;
           animated.nFrames = 1;
           drawable.srcY = source_y(idleSourceY, movable.dominantDirection);
         });
}

void enter_move(entt::registry& registry,
                entt::entity entity,
                Direction direction)
{
  update(
      registry,
      entity,
      [direction](Animated& animated, Movable&, Drawable& drawable) noexcept {
        animated.frame = 0;
        animated.nFrames = 9;
        animated.delay = 90;
        drawable.srcY = source_y(moveSourceY, direction);
      });
}

void enter_spell(entt::registry&, entt::entity)
{
  // TODO
}

void humanoid_update_move(entt::registry& registry, entt::entity entity)
{
  update(registry,
         entity,
         [](Animated& animated, Movable& movable, Drawable& drawable) noexcept {
           const auto srcY = source_y(moveSourceY, movable.dominantDirection);
           if (drawable.srcY != srcY) {
             animated.frame = 0;
             drawable.srcY = srcY;
           }
         });
}

}  // namespace wanderer
