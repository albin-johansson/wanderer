#include "humanoid_animation_system.h"

#include "animated.h"
#include "drawable.h"
#include "humanoid_state.h"
#include "movable.h"

namespace wanderer {
namespace {

inline constexpr int idleSourceY = 512;  // yes these are the same
inline constexpr int moveSourceY = 512;
inline constexpr int meleeSourceY = 768;

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

void humanoid_update_move_animation(entt::registry& registry,
                                    entt::entity entity)
{
  update(registry,
         entity,
         [](Animated& animated, Movable& movable, Drawable& drawable) noexcept {
           drawable.srcX = movable.velocity.is_zero()
                               ? 0
                               : static_cast<int>(animated.frame) * 64;
           const auto srcY = source_y(moveSourceY, movable.dominantDirection);
           if (drawable.srcY != srcY) {
             animated.frame = 0;
             drawable.srcY = srcY;
           }
         });
}

void humanoid_update_attack_animation(entt::registry& registry,
                                      entt::entity entity)
{
  update(registry,
         entity,
         [&registry, entity](
             Animated& animated, Movable&, Drawable& drawable) noexcept {
           drawable.srcX = static_cast<int>(animated.frame) * 64;
           if (animated.frame == animated.nFrames - 1) {
             if (auto* attack = registry.try_get<HumanoidAttack>(entity);
                 attack) {
               attack->done = true;
             }
           }
         });
}

}  // namespace

void humanoid_enter_idle_animation(entt::registry& registry,
                                   entt::entity entity)
{
  update(registry,
         entity,
         [](Animated& animated, Movable& movable, Drawable& drawable) noexcept {
           animated.frame = 0;
           animated.nFrames = 1;
           drawable.srcX = 0;
           drawable.srcY = source_y(idleSourceY, movable.dominantDirection);
         });
}

void humanoid_enter_move_animation(entt::registry& registry,
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
        drawable.srcX = 0;
        drawable.srcY = source_y(moveSourceY, direction);
      });
}

void humanoid_enter_melee_animation(entt::registry& registry,
                                    entt::entity entity)
{
  update(registry,
         entity,
         [](Animated& animated, Movable& movable, Drawable& drawable) noexcept {
           animated.frame = 0;
           animated.nFrames = 6;
           drawable.srcX = 0;
           drawable.srcY = source_y(meleeSourceY, movable.dominantDirection);
         });
}

void humanoids_update_animation(entt::registry& registry)
{
  const auto entities = registry.view<Humanoid>();
  for (const auto entity : entities) {
    if (registry.has<HumanoidMove>(entity)) {
      humanoid_update_move_animation(registry, entity);
    }
    if (registry.has<HumanoidAttack>(entity)) {
      humanoid_update_attack_animation(registry, entity);
    }
  }
}

}  // namespace wanderer
