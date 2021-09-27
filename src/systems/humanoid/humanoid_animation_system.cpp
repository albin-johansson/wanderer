#include "humanoid_animation_system.hpp"

#include <cassert>  // assert

#include "common/milliseconds.hpp"
#include "components/ai/humanoid_state.hpp"
#include "components/gfx/animated.hpp"
#include "components/gfx/depth_drawable.hpp"
#include "components/physics/movable.hpp"

namespace wanderer::sys {
namespace {

inline constexpr int n_idle_frames{1};
inline constexpr int n_move_frames{9};
inline constexpr int n_melee_frames{6};
inline constexpr int n_magic_frames{7};
inline constexpr int n_spear_frames{8};
inline constexpr int n_bow_frames{13};

inline constexpr int magic_source_y{0};
inline constexpr int spear_source_y{256};
inline constexpr int idle_source_y{512};  // yes these are the same
inline constexpr int move_source_y{512};
inline constexpr int melee_source_y{768};
inline constexpr int bow_source_y{1024};

inline constexpr ms_t idle_delay{90};
inline constexpr ms_t move_delay{55};
inline constexpr ms_t attack_delay{70};

/**
 * \brief Returns the y-coordinate with the appropriate offset in relation to
 * the dir.
 *
 * \note This function assumes that all humanoids use an LPC tilesheet.
 *
 * \param y the base y-coordinate for the type of animation.
 * \param dir the dir of the humanoid used to determine the
 * appropriate offset.
 *
 * \return the source y-coordinate to use for rendering a humanoid.
 */
[[nodiscard]] constexpr auto source_y(const int y, const direction dir) noexcept -> int
{
  switch (dir) {
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
void update_move_animation(entt::registry& registry, const entt::entity entity)
{
  auto& animated = registry.get<comp::animated>(entity);
  auto& drawable = registry.get<comp::depth_drawable>(entity);
  const auto& movable = registry.get<comp::movable>(entity);

  drawable.src.set_x(movable.velocity.is_zero() ? 0 : animated.frame * 64);
  const auto srcY = source_y(move_source_y, movable.dir);
  if (drawable.src.y() != srcY) {
    animated.frame = 0;
    drawable.src.set_y(srcY);
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
void update_attack_animation(entt::registry& registry, const entt::entity entity)
{
  assert(registry.all_of<comp::humanoid_attack>(entity));

  auto& animated = registry.get<comp::animated>(entity);
  auto& drawable = registry.get<comp::depth_drawable>(entity);

  drawable.src.set_x(animated.frame * 64);
  if (animated.frame == animated.frame_count - 1) {
    auto& attack = registry.get<comp::humanoid_attack>(entity);
    attack.done = true;
  }
}

/**
 * \brief Sets the animation of an entity.
 *
 * \note This function only works for LPC spritesheets. Which should be used
 * for all humanoids.
 *
 * \param registry the current level registry.
 * \param entity the entity that will enter the animation.
 * \param nFrames the number of frames in the animation.
 * \param delay the duration of each frame in the animation.
 * \param sourceY the base y-coordinate in the source tilesheet for the
 * animation.
 */
void enter_animation(entt::registry& registry,
                     const entt::entity entity,
                     const uint32 nFrames,
                     const ms_t delay,
                     const int sourceY)
{
  auto& animated = registry.get<comp::animated>(entity);
  animated.frame = 0;
  animated.frame_count = nFrames;
  animated.delay = delay;

  auto& drawable = registry.get<comp::depth_drawable>(entity);
  const auto& movable = registry.get<comp::movable>(entity);
  drawable.src.set_x(0);
  drawable.src.set_y(source_y(sourceY, movable.dir));
}

void enter_animation(entt::registry& registry,
                     const entt::entity entity,
                     const uint32 nFrames,
                     const ms_t delay,
                     const int sourceY,
                     const direction dir)
{
  auto& animated = registry.get<comp::animated>(entity);
  animated.frame = 0;
  animated.frame_count = nFrames;
  animated.delay = delay;

  auto& drawable = registry.get<comp::depth_drawable>(entity);
  drawable.src.set_x(0);
  drawable.src.set_y(source_y(sourceY, dir));
}

}  // namespace

void enter_idle_animation(entt::registry& registry, const entt::entity entity)
{
  enter_animation(registry, entity, n_idle_frames, idle_delay, idle_source_y);
}

void enter_move_animation(entt::registry& registry,
                          const entt::entity entity,
                          const direction dir)
{
  enter_animation(registry,
                  entity,
                  n_move_frames,
                  move_delay,
                  source_y(move_source_y, dir),
                  dir);
}

void enter_melee_animation(entt::registry& registry, const entt::entity entity)
{
  enter_animation(registry, entity, n_melee_frames, attack_delay, melee_source_y);
}

void enter_spell_animation(entt::registry& registry, const entt::entity entity)
{
  enter_animation(registry, entity, n_magic_frames, attack_delay, magic_source_y);
}

void enter_bow_animation(entt::registry& registry, const entt::entity entity)
{
  enter_animation(registry, entity, n_bow_frames, attack_delay, bow_source_y);
}

void enter_spear_animation(entt::registry& registry, const entt::entity entity)
{
  enter_animation(registry, entity, n_spear_frames, attack_delay, spear_source_y);
}

void update_humanoid_animations(entt::registry& registry)
{
  for (auto&& [entity] : registry.view<comp::humanoid>().each()) {
    if (registry.all_of<comp::humanoid_move>(entity)) {
      update_move_animation(registry, entity);
    }
    else if (registry.all_of<comp::humanoid_attack>(entity)) {
      update_attack_animation(registry, entity);
    }
  }
}

}  // namespace wanderer::sys
