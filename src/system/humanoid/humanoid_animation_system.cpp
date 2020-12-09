#include "humanoid_animation_system.hpp"

#include <cassert>  // assert

#include "component/animated.hpp"
#include "component/depth_drawable.hpp"
#include "component/humanoid_state.hpp"
#include "component/movable.hpp"
#include "milliseconds.hpp"

namespace wanderer::sys::humanoid {
namespace {

inline constexpr int g_nIdleFrames{1};
inline constexpr int g_nMeleeFrames{6};
inline constexpr int g_nMagicFrames{7};
inline constexpr int g_nSpearFrames{8};
inline constexpr int g_nBowFrames{13};

inline constexpr int g_magicSourceY{0};
inline constexpr int g_spearSourceY{256};
inline constexpr int g_idleSourceY{512};  // yes these are the same
inline constexpr int g_moveSourceY{512};
inline constexpr int g_meleeSourceY{768};
inline constexpr int g_bowSourceY{1024};

inline constexpr ms_t g_idleDelay{90};
inline constexpr ms_t g_moveDelay{70};
inline constexpr ms_t g_attackDelay{70};

/**
 * \brief Returns the y-coordinate with the appropriate offset in relation to
 * the direction.
 *
 * \note This method assumes that all humanoids use an LPC tilesheet.
 *
 * \param y the base y-coordinate for the type of animation.
 * \param direction the direction of the humanoid used to determine the
 * appropriate offset.
 * \return the source y-coordinate to use for rendering a humanoid.
 */
[[nodiscard]] auto source_y(const int y, const direction direction) noexcept
    -> int
{
  switch (direction) {
    default:
      assert(false);
    case direction::up:
      return y;
    case direction::left:
      return y + 64;
    case direction::down:
      return y + 128;
    case direction::right:
      return y + 192;
  }
}

/**
 * \brief Updates the movement animation of a humanoid.
 *
 * \param registry the associated registry.
 * \param entity the entity that will be updated.
 */
void update_move_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  auto* animated = registry.try_get<comp::animated>(entity);
  auto* drawable = registry.try_get<comp::depth_drawable>(entity);
  const auto* movable = registry.try_get<comp::movable>(entity);

  if (animated && drawable && movable) {
    drawable->src.set_x(movable->velocity.is_zero() ? 0 : animated->frame * 64);
    const auto srcY = source_y(g_moveSourceY, movable->dir);
    if (drawable->src.y() != srcY) {
      animated->frame = 0;
      drawable->src.set_y(srcY);
    }
  }
}

/**
 * \brief Updates the attack animation of a humanoid.
 *
 * \pre `entity` must have a `humanoid_attack` component.
 *
 * \param registry the associated registry.
 * \param entity the entity that will be updated.
 */
void update_attack_animation(entt::registry& registry,
                             const entt::entity entity) noexcept
{
  assert(registry.has<comp::humanoid_attack>(entity));
  auto* animated = registry.try_get<comp::animated>(entity);
  auto* drawable = registry.try_get<comp::depth_drawable>(entity);

  if (animated && drawable) {
    drawable->src.set_x(animated->frame * 64);
    if (animated->frame == animated->nFrames - 1) {
      auto& attack = registry.get<comp::humanoid_attack>(entity);
      attack.done = true;
    }
  }
}

/**
 * \brief General method for entering an animation.
 *
 * \note This method only works for LPC spritesheets. Which should be used
 * for all humanoids.
 *
 * \param registry the associated registry.
 * \param entity the entity that will enter the animation.
 * \param nFrames the number of frames in the animation.
 * \param delay the duration of each frame in the animation.
 * \param sourceY the base y-coordinate in the source tilesheet for the
 * animation.
 */
void enter_animation(entt::registry& registry,
                     const entt::entity entity,
                     const u32 nFrames,
                     const ms_t delay,
                     const int sourceY) noexcept
{
  auto* animated = registry.try_get<comp::animated>(entity);
  auto* drawable = registry.try_get<comp::depth_drawable>(entity);
  const auto* movable = registry.try_get<comp::movable>(entity);

  if (animated && drawable && movable) {
    animated->frame = 0;
    animated->nFrames = nFrames;
    animated->delay = delay;
    drawable->src.set_x(0);
    drawable->src.set_y(source_y(sourceY, movable->dir));
  }
}

}  // namespace

void enter_idle_animation(entt::registry& registry,
                          const entt::entity entity) noexcept
{
  enter_animation(registry, entity, g_nIdleFrames, g_idleDelay, g_idleSourceY);
}

void enter_move_animation(entt::registry& registry,
                          const entt::entity entity,
                          const direction direction) noexcept
{
  auto* animated = registry.try_get<comp::animated>(entity);
  auto* drawable = registry.try_get<comp::depth_drawable>(entity);

  if (animated && drawable) {
    animated->frame = 0;
    animated->nFrames = 9;
    animated->delay = g_moveDelay;
    drawable->src.set_x(0);
    drawable->src.set_y(source_y(g_moveSourceY, direction));
  }
}

void enter_melee_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  enter_animation(registry,
                  entity,
                  g_nMeleeFrames,
                  g_attackDelay,
                  g_meleeSourceY);
}

void enter_spell_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  enter_animation(registry,
                  entity,
                  g_nMagicFrames,
                  g_attackDelay,
                  g_magicSourceY);
}

void enter_bow_animation(entt::registry& registry,
                         const entt::entity entity) noexcept
{
  enter_animation(registry, entity, g_nBowFrames, g_attackDelay, g_bowSourceY);
}

void enter_spear_animation(entt::registry& registry,
                           const entt::entity entity) noexcept
{
  enter_animation(registry,
                  entity,
                  g_nSpearFrames,
                  g_attackDelay,
                  g_spearSourceY);
}

void update_animation(entt::registry& registry)
{
  registry.view<comp::humanoid>().each([&](const entt::entity entity) {
    if (registry.has<comp::humanoid_move>(entity)) {
      update_move_animation(registry, entity);
    }
    if (registry.has<comp::humanoid_attack>(entity)) {
      update_attack_animation(registry, entity);
    }
  });
}

}  // namespace wanderer::sys::humanoid
