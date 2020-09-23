#include "humanoid_animation_system.hpp"

#include <type_traits>

#include "component/animated.hpp"
#include "component/depth_drawable.hpp"
#include "component/humanoid_state.hpp"
#include "component/movable.hpp"

namespace wanderer::sys::humanoid {
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
    Lambda&& lambda) noexcept(noexcept(lambda(std::declval<comp::animated&>(),
                                              std::declval<comp::movable&>(),
                                              std::declval<
                                                  comp::depth_drawable&>())))
{
  if (registry.has<comp::animated, comp::movable, comp::depth_drawable>(
          entity)) {
    auto& animated = registry.get<comp::animated>(entity);
    auto& movable = registry.get<comp::movable>(entity);
    auto& drawable = registry.get<comp::depth_drawable>(entity);
    lambda(animated, movable, drawable);
  }
}

/**
 * @brief Returns the y-coordinate with the appropriate offset in relation to
 * the direction.
 *
 * @note This method assumes that all humanoids use an LPC tilesheet.
 *
 * @param y the base y-coordinate for the type of animation.
 * @param direction the direction of the humanoid used to determine the
 * appropriate offset.
 * @return the source y-coordinate to use for rendering a humanoid.
 */
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

/**
 * @brief Updates the movement animation of a humanoid.
 *
 * @param registry the associated registry.
 * @param entity the entity that will be updated.
 */
void update_move_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  update(registry,
         entity,
         [](comp::animated& animated,
            comp::movable& movable,
            comp::depth_drawable& drawable) noexcept {
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

/**
 * @brief Updates the attack animation of a humanoid.
 *
 * @pre `entity` must have a `humanoid_attack` component.
 *
 * @param registry the associated registry.
 * @param entity the entity that will be updated.
 */
void update_attack_animation(entt::registry& registry,
                             const entt::entity entity) noexcept
{
  update(registry,
         entity,
         [&registry, entity](comp::animated& animated,
                             comp::movable&,
                             comp::depth_drawable& drawable) noexcept {
           drawable.src.set_x(static_cast<int>(animated.frame) * 64);
           if (animated.frame == animated.nFrames - 1) {
             auto& attack = registry.get<comp::humanoid_attack>(entity);
             attack.done = true;
           }
         });
}

/**
 * @brief General method for entering an animation.
 *
 * @note This method only works for LPC spritesheets. Which should be used
 * for all humanoids.
 *
 * @param registry the associated registry.
 * @param entity the entity that will enter the animation.
 * @param nFrames the number of frames in the animation.
 * @param delay the duration of each frame in the animation.
 * @param sourceY the base y-coordinate in the source tilesheet for the
 * animation.
 */
void enter_animation(entt::registry& registry,
                     const entt::entity entity,
                     const u32 nFrames,
                     const u32 delay,
                     const int sourceY) noexcept
{
  update(registry,
         entity,
         [nFrames, sourceY, delay](comp::animated& animated,
                                   comp::movable& movable,
                                   comp::depth_drawable& drawable) noexcept {
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
         [direction](comp::animated& animated,
                     comp::movable&,
                     comp::depth_drawable& drawable) noexcept {
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
  const auto entities = registry.view<comp::humanoid>();
  for (const auto entity : entities) {
    if (registry.has<comp::humanoid_move>(entity)) {
      update_move_animation(registry, entity);
    }
    if (registry.has<comp::humanoid_attack>(entity)) {
      update_attack_animation(registry, entity);
    }
  }
}

}  // namespace wanderer::sys::humanoid
