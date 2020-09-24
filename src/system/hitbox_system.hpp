#pragma once

#include <entt.hpp>

#include "component/hitbox.hpp"
#include "vector2.hpp"

namespace wanderer::sys::hitbox {

void update_collision(entt::registry& registry);

/**
 * @brief Updates the bounds of a hitbox.
 *
 * @details Verifies and updates the state of the bounds of a hitbox. The bounds
 * is the bounding rectangle that covers all of the subhitboxes in a hitbox.
 *
 * @param hitbox the hitbox that will be updated.
 */
void update_bounds(comp::hitbox& hitbox) noexcept;

/**
 * @brief Updates the position of a hitbox.
 *
 * @param hitbox the hitbox that will be moved.
 * @param position the new position of the hitbox.
 */
void update_position(comp::hitbox& hitbox, const vector2f& position) noexcept;

/**
 * @brief Indicates whether or not two hitboxes intersect.
 *
 * @details Determines whether or not two hitboxes are currently intersecting
 * each other.
 *
 * @note Checking whether or not a hitbox intersects itself will result in the
 * method returning `false`.
 * @code{.cpp}
 * Hitbox hbox = ...;
 * bool res = hitbox::intersects(hbox, hbox); // This will always return false!
 * @endcode
 *
 * @param fst the first hitbox.
 * @param snd the second hitbox.
 * @return `true` if the hitboxes intersect; `false` otherwise.
 */
[[nodiscard]] auto intersects(const comp::hitbox& fst,
                              const comp::hitbox& snd) noexcept -> bool;

/**
 * @brief Creates and returns a hitbox.
 *
 * @details This function is for convenience and will update the bounds of the
 * created hitbox before returning it.
 *
 * @param boxes the subhitboxes that will be added to the hitbox.
 *
 * @return a hitbox.
 *
 * @since 0.1.0
 */
[[nodiscard]] inline auto create(std::vector<comp::subhitbox>&& boxes)
    -> comp::hitbox
{
  using comp::hitbox;

  hitbox hb;
  hb.boxes = std::move(boxes);

  update_bounds(hb);

  return hb;
}

}  // namespace wanderer::sys::hitbox
