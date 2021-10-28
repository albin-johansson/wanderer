#pragma once

#include <initializer_list>  // initializer_list

#include <rune/everything.hpp>  // delta_time

#include "components/hitbox.hpp"
#include "components/movable.hpp"
#include "wanderer_std.hpp"

namespace wanderer::sys {

/// \name Movement
/// \{

/// \brief Represents a pair of two hypothetical future hitboxes.
/// \ingroup systems
struct NextHitboxes final
{
  maybe<comp::Hitbox> horizontal;  ///< The next hitbox with only a horizontal offset.
  maybe<comp::Hitbox> vertical;    ///< The next hitbox with only a vertical offset.
};

/// \brief Represents a collision result in two axes.
/// \ingroup systems
struct CollisionResult final
{
  bool horizontal{};  ///< Indicates whether or not there was a horizontal collision.
  bool vertical{};    ///< Indicates whether or not there was a vertical collision.
};

/**
 * \brief Updates the bounds of a hitbox.
 *
 * \details This function verifies and updates the state of the bounds of a hitbox, i.e.
 * the rectangle that covers all of the subhitboxes in the hitbox.
 *
 * \ingroup systems
 *
 * \param hitbox the hitbox that will be updated.
 */
void UpdateBounds(comp::Hitbox& hitbox) noexcept;

/**
 * \brief Sets the position of a hitbox and updates its bounds.
 *
 * \ingroup systems
 *
 * \param hitbox the hitbox that will be moved.
 * \param position the new position of the hitbox.
 */
void SetPosition(comp::Hitbox& hitbox, float2 position) noexcept;

/**
 * \brief Creates a copy of the supplied hitbox with the specified position.
 *
 * \ingroup systems
 *
 * \param hitbox the source hitbox.
 * \param position the position of the new hitbox.
 *
 * \return a hitbox that is a copy of the supplied hitbox with the specified position.
 */
[[nodiscard]] auto WithPosition(const comp::Hitbox& hitbox, float2 position) noexcept
    -> comp::Hitbox;

/**
 * \brief Indicates whether or not two hitboxes intersect.
 *
 * \note Hitboxes are not considered to intersect themselves.
 *
 * \ingroup systems
 *
 * \param fst the first hitbox.
 * \param snd the second hitbox.
 *
 * \return `true` if the hitboxes intersect; `false` otherwise.
 */
[[nodiscard]] auto Intersects(const comp::Hitbox& fst, const comp::Hitbox& snd) noexcept
    -> bool;

/**
 * \brief Creates a hitbox.
 *
 * \ingroup systems
 *
 * \param boxes the subhitboxes that will constitute the hitbox.
 *
 * \return a hitbox with the specified subhitboxes.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto MakeHitbox(std::initializer_list<comp::Subhitbox> boxes)
    -> comp::Hitbox;

/**
 * \brief Calculates the next theoretical hitboxes for a movable entity.
 *
 * \details This function is used for collision detection, where these future hitboxes are
 * used to determine whether or not an entity can move either vertically or horizontally
 * with the current delta time.
 *
 * \ingroup systems
 *
 * \param movable the current movable component.
 * \param hitbox the current hitbox.
 * \param oldPosition the previous position of the hitbox.
 * \param dt the current delta time.
 *
 * \return the next theoretical vertical and horizontal hitboxes.
 */
[[nodiscard]] auto MakeNextHitboxes(const comp::Movable& movable,
                                    const comp::Hitbox& hitbox,
                                    float2 oldPosition,
                                    float dt) -> NextHitboxes;

/**
 * \brief Computes the collisions for a pair of future hitboxes and an obstacle.
 *
 * \details This function performs collision detection between the future hitboxes and the
 * obstacle hitbox. However, this function is only meant to be used with likely collision
 * candidates, since this function will iterate all subhitboxes of the objects to check if
 * they collide. In other words, this function has quadratic complexity, but it's fine as
 * long as the AABB tree is used to determine likely collision candidates.
 *
 * \ingroup systems
 *
 * \param next the theoretical hitboxes, probably obtained through `MakeNextHitboxes()`.
 * \param obstacle the hitbox of the obstacle.
 *
 * \return the vertical and horizontal collision results.
 */
[[nodiscard]] auto QueryCollisions(const NextHitboxes& next, const comp::Hitbox& obstacle)
    -> CollisionResult;

/// \} End of movement

}  // namespace wanderer::sys
