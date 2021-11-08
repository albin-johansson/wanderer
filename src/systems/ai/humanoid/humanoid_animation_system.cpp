#include "humanoid_animation_system.hpp"

#include <cassert>  // assert

#include "components/animation.hpp"
#include "components/drawable.hpp"
#include "components/humanoid.hpp"
#include "components/movable.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {
namespace {

constexpr int32 n_idle_frames{1};
constexpr int32 n_move_frames{9};
constexpr int32 n_melee_frames{6};
constexpr int32 n_magic_frames{7};
constexpr int32 n_spear_frames{8};
constexpr int32 n_bow_frames{13};

constexpr int32 magic_source_y{0};
constexpr int32 spear_source_y{256};
constexpr int32 idle_source_y{512};  // yes these are the same
constexpr int32 move_source_y{512};
constexpr int32 melee_source_y{768};
constexpr int32 bow_source_y{1024};

constexpr ms_t idle_delay{90};
constexpr ms_t move_delay{55};
constexpr ms_t attack_delay{70};

/**
 * \brief Returns the y-coordinate with the appropriate offset in relation to the
 * direction.
 *
 * \note This function assumes that all humanoids use an LPC tilesheet.
 *
 * \param y the base y-coordinate for the type of animation.
 * \param dir the direction of the humanoid used to determine the appropriate offset.
 *
 * \return the source y-coordinate to use for rendering a humanoid.
 */
[[nodiscard]] constexpr auto GetSourceY(const int32 y, const Direction dir) noexcept
    -> int32
{
  switch (dir) {
    default:
      assert(false);

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
 * \brief Updates the movement animation of a humanoid.
 *
 * \param registry the associated registry.
 * \param entity the entity that will be updated.
 */
void UpdateMoveAnimation(entt::registry& registry, const entt::entity entity)
{
  auto& animation = registry.get<Animation>(entity);
  auto& drawable = registry.get<Drawable>(entity);
  const auto& movable = registry.get<Movable>(entity);

  drawable.src.set_x(IsZero(movable.velocity) ? 0
                                              : static_cast<int32>(animation.frame) * 64);
  const auto srcY = GetSourceY(move_source_y, movable.dir);
  if (drawable.src.y() != srcY) {
    animation.frame = 0u;
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
void UpdateAttackAnimation(entt::registry& registry, const entt::entity entity)
{
  assert(registry.all_of<HumanoidAttack>(entity));

  auto& animation = registry.get<Animation>(entity);
  auto& drawable = registry.get<Drawable>(entity);

  drawable.src.set_x(static_cast<int32>(animation.frame) * 64);
  if (animation.frame == animation.frame_count - 1u) {
    auto& attack = registry.get<HumanoidAttack>(entity);
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
void EnterAnimation(entt::registry& registry,
                    const entt::entity entity,
                    const uint32 nFrames,
                    const ms_t delay,
                    const int32 sourceY)
{
  auto& animation = registry.get<Animation>(entity);
  animation.frame = 0;
  animation.frame_count = nFrames;
  animation.delay = delay;

  auto& drawable = registry.get<Drawable>(entity);
  const auto& movable = registry.get<Movable>(entity);
  drawable.src.set_x(0);
  drawable.src.set_y(GetSourceY(sourceY, movable.dir));
}

void EnterAnimation(entt::registry& registry,
                    const entt::entity entity,
                    const uint32 nFrames,
                    const ms_t delay,
                    const int32 sourceY,
                    const Direction dir)
{
  auto& animation = registry.get<Animation>(entity);
  animation.frame = 0;
  animation.frame_count = nFrames;
  animation.delay = delay;

  auto& drawable = registry.get<Drawable>(entity);
  drawable.src.set_x(0);
  drawable.src.set_y(GetSourceY(sourceY, dir));
}

}  // namespace

void EnterIdleAnimation(entt::registry& registry, entt::entity entity)
{
  EnterAnimation(registry, entity, n_idle_frames, idle_delay, idle_source_y);
}

void EnterMoveAnimation(entt::registry& registry, entt::entity entity, Direction dir)
{
  EnterAnimation(registry,
                 entity,
                 n_move_frames,
                 move_delay,
                 GetSourceY(move_source_y, dir),
                 dir);
}

void EnterMeleeAnimation(entt::registry& registry, entt::entity entity)
{
  EnterAnimation(registry, entity, n_melee_frames, attack_delay, melee_source_y);
}

void EnterSpellAnimation(entt::registry& registry, entt::entity entity)
{
  EnterAnimation(registry, entity, n_magic_frames, attack_delay, magic_source_y);
}

void EnterBowAnimation(entt::registry& registry, entt::entity entity)
{
  EnterAnimation(registry, entity, n_bow_frames, attack_delay, bow_source_y);
}

void EnterSpearAnimation(entt::registry& registry, entt::entity entity)
{
  EnterAnimation(registry, entity, n_spear_frames, attack_delay, spear_source_y);
}

void UpdateHumanoidAnimations(entt::registry& registry)
{
  for (auto&& [entity] : registry.view<Humanoid>().each()) {
    if (registry.all_of<HumanoidMove>(entity)) {
      UpdateMoveAnimation(registry, entity);
    }
    else if (registry.all_of<HumanoidAttack>(entity)) {
      UpdateAttackAnimation(registry, entity);
    }
  }
}

}  // namespace wanderer::sys
