#pragma once

#include <entt.hpp>
#include <initializer_list>  // initializer_list

#include "delta.hpp"
#include "hitbox.hpp"
#include "maybe.hpp"
#include "movable.hpp"
#include "vector2.hpp"

namespace wanderer::sys {

struct next_hitboxes final
{
  maybe<comp::hitbox> horizontal;
  maybe<comp::hitbox> vertical;
};

struct collision_result final
{
  bool horizontal{};
  bool vertical{};
};

/**
 * \brief Updates the bounds of a hitbox.
 *
 * \details Verifies and updates the state of the bounds of a hitbox. The bounds
 * is the bounding rectangle that covers all of the subhitboxes in a hitbox.
 *
 * \param hitbox the hitbox that will be updated.
 */
void update_bounds(comp::hitbox& hitbox) noexcept;

/**
 * \brief Updates the position of a hitbox.
 *
 * \param hitbox the hitbox that will be moved.
 * \param position the new position of the hitbox.
 */
void set_position(comp::hitbox& hitbox, const vector2f& position) noexcept;

[[nodiscard]] auto with_position(const comp::hitbox& hitbox,
                                 const vector2f& position) noexcept
    -> comp::hitbox;

/**
 * \brief Indicates whether or not two hitboxes intersect.
 *
 * \details Determines whether or not two hitboxes are currently intersecting
 * each other.
 *
 * \note Checking whether or not a hitbox intersects itself will result in the
 * method returning `false`.
 *
 * \param fst the first hitbox.
 * \param snd the second hitbox.
 *
 * \return `true` if the hitboxes intersect; `false` otherwise.
 */
[[nodiscard]] auto intersects(const comp::hitbox& fst,
                              const comp::hitbox& snd) noexcept -> bool;

/**
 * \brief Creates and returns a hitbox.
 *
 * \details This function is for convenience and will update the bounds of the
 * created hitbox before returning it.
 *
 * \param boxes the subhitboxes that will be added to the hitbox.
 *
 * \return a hitbox.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto create_hitbox(std::initializer_list<comp::subhitbox> boxes)
    -> comp::hitbox;

[[nodiscard]] auto make_next_hitboxes(const comp::movable& movable,
                                      const comp::hitbox& hitbox,
                                      const vector2f& oldPosition,
                                      delta_t dt) -> next_hitboxes;

[[nodiscard]] auto query_collisions(const next_hitboxes& next,
                                    const comp::hitbox& other)
    -> collision_result;

}  // namespace wanderer::sys
