#include "humanoid_animation_system.h"

#include <type_traits>

#include "animated.h"
#include "depth_drawable.h"
#include "humanoid_state.h"
#include "movable.h"

namespace wanderer::system::humanoid {
namespace {

inline constexpr int nIdleFrames{1};
inline constexpr int nMeleeFrames{6};
inline constexpr int nMagicFrames{7};
inline constexpr int nSpearFrames{8};
inline constexpr int nBowFrames{13};

inline constexpr int magicSourceY{0};
inline constexpr int spearSourceY{256};
inline constexpr int idleSourceY{512};  // yes these are the same
inline constexpr int moveSourceY{512};
inline constexpr int meleeSourceY{768};
inline constexpr int bowSourceY{1024};

inline constexpr u32 idleDelay{90};
inline constexpr u32 moveDelay{70};
inline constexpr u32 attackDelay{70};

template <typename Lambda>
void update(
    entt::registry& registry,
    const entt::entity entity,
    Lambda&& lambda) noexcept(noexcept(lambda(std::declval<Animated&>(),
                                              std::declval<Movable&>(),
                                              std::declval<DepthDrawable&>())))
{
  if (registry.has<Animated, Movable, DepthDrawable>(entity)) {
    auto& animated = registry.get<Animated>(entity);
    auto& movable = registry.get<Movable>(entity);
    auto& drawable = registry.get<DepthDrawable>(entity);
    lambda(animated, movable, drawable);
  }
}

[[nodiscard]] auto source_y(const int y, const Direction direction) noexcept
    -> int
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
                                    const entt::entity entity) noexcept
{
  update(registry,
         entity,
         [](Animated& animated,
            Movable& movable,
            DepthDrawable& drawable) noexcept {
           drawable.src.set_x(movable.velocity.is_zero()
                                  ? 0
                                  : static_cast<int>(animated.frame) * 64);
           const auto srcY = source_y(moveSourceY, movable.dominantDirection);
           if (drawable.src.y() != srcY) {
             animated.frame = 0;
             drawable.src.set_y(srcY);
           }
         });
}

void humanoid_update_attack_animation(entt::registry& registry,
                                      const entt::entity entity) noexcept
{
  update(registry,
         entity,
         [&registry, entity](
             Animated& animated, Movable&, DepthDrawable& drawable) noexcept {
           drawable.src.set_x(static_cast<int>(animated.frame) * 64);
           if (animated.frame == animated.nFrames - 1) {
             if (auto* attack = registry.try_get<HumanoidAttack>(entity);
                 attack) {
               attack->done = true;
             }
           }
         });
}

void enter_animation(entt::registry& registry,
                     const entt::entity entity,
                     const u32 nFrames,
                     const u32 delay,
                     const int sourceY) noexcept
{
  update(registry,
         entity,
         [nFrames, sourceY, delay](Animated& animated,
                                   Movable& movable,
                                   DepthDrawable& drawable) noexcept {
           animated.frame = 0;
           animated.nFrames = nFrames;
           animated.delay = delay;
           drawable.src.set_x(0);
           drawable.src.set_y(source_y(sourceY, movable.dominantDirection));
         });
}

}  // namespace

void enter_idle_animation(entt::registry& registry,
                          const entt::entity entity) noexcept
{
  enter_animation(registry, entity, nIdleFrames, idleDelay, idleSourceY);
}

void enter_move_animation(entt::registry& registry,
                          const entt::entity entity,
                          const Direction direction) noexcept
{
  update(registry,
         entity,
         [direction](
             Animated& animated, Movable&, DepthDrawable& drawable) noexcept {
           animated.frame = 0;
           animated.nFrames = 9;
           animated.delay = moveDelay;
           drawable.src.set_x(0);
           drawable.src.set_y(source_y(moveSourceY, direction));
         });
}

void enter_melee_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  enter_animation(registry, entity, nMeleeFrames, attackDelay, meleeSourceY);
}

void enter_spell_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  enter_animation(registry, entity, nMagicFrames, attackDelay, magicSourceY);
}

void enter_bow_animation(entt::registry& registry,
                         const entt::entity entity) noexcept
{
  enter_animation(registry, entity, nBowFrames, attackDelay, bowSourceY);
}

void enter_spear_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  enter_animation(registry, entity, nSpearFrames, attackDelay, spearSourceY);
}

void update_animation(entt::registry& registry)
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

}  // namespace wanderer::system::humanoid
