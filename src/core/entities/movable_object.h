#pragma once
#include <type_traits>

#include "direction.h"
#include "game_object.h"
#include "vector_2.h"

namespace albinjohansson::wanderer {

class IGameObject;

/**
 * The IMovableObject interface specifies game objects that are movable.
 *
 * @see IGameObject
 * @since 0.1.0
 */
class IMovableObject : public virtual IGameObject {
 public:
  ~IMovableObject() override = default;

  /**
   * Specifies a direction the movable should attempt to move in. Note, movable
   * game objects can move in up to two different directions at once. This
   * method merely tells the game object where to move when updated, and as
   * such, has no immediate effect on the position of the object.
   *
   * @param direction the direction to attempt to move in when updated (a
   * movable object can move in up to two different directions at once).
   * @since 0.1.0
   */
  virtual void move(Direction direction) noexcept = 0;

  /**
   * Stops the movement of the object in the specified direction. Note! This
   * doesn't necessarily stop the game object.
   *
   * @param direction the direction in which movement should be ceased.
   * @since 0.1.0
   */
  virtual void stop(Direction direction) noexcept = 0;

  /**
   * Ceases any movement of the object.
   *
   * @since 0.1.0
   */
  virtual void stop() noexcept = 0;

  /**
   * Interpolates the previous position of the object with the current position.
   * Use the IMovable::GetInterpolatedPosition method to obtain the affected
   * vector.
   *
   * @param alpha the interpolation coefficient, in the range [0, 1].
   * @since 0.1.0
   */
  virtual void interpolate(float alpha) noexcept = 0;

  /**
   * Adds the supplied offset to the x-coordinate of the object.
   *
   * @param dx the x-axis offset, may be negative.
   * @since 0.1.0
   */
  virtual void add_x(float dx) noexcept = 0;

  /**
   * Adds the supplied offset to the y-coordinate of the object.
   *
   * @param dy the y-axis offset, may be negative.
   * @since 0.1.0
   */
  virtual void add_y(float dy) noexcept = 0;

  /**
   * Sets the x-coordinate of the object.
   *
   * @param x the new x-coordinate of the object.
   * @since 0.1.0
   */
  virtual void set_x(float x) noexcept = 0;

  /**
   * Sets the y-coordinate of the object.
   *
   * @param y the new y-coordinate of the object.
   * @since 0.1.0
   */
  virtual void set_y(float y) noexcept = 0;

  /**
   * Sets the total speed of the movable.
   *
   * @param speed the new total speed of the movable.
   * @since 0.1.0
   */
  virtual void set_speed(float speed) noexcept = 0;

  /**
   * Sets the current velocity of the movable.
   *
   * @param velocity the vector that represents the new velocity.
   * @since 0.1.0
   */
  virtual void set_velocity(const Vector2& velocity) noexcept = 0;

  [[nodiscard]] virtual bool will_intersect(const IGameObject* other,
                                            float delta) const = 0;

  /**
   * Returns the movement speed of the movable. Note! This is not the same as
   * the velocity of the movable, but merely the maximum allowed speed.
   *
   * @return the movement speed of the movable.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float get_speed() const noexcept = 0;

  /**
   * Returns the dominant direction of the movable object.
   *
   * @return the dominant direction of the movable object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual Direction get_dominant_direction() const noexcept = 0;

  /**
   * Returns the previous position of the movable object.
   *
   * @return the previous position of the movable object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual const Vector2& get_previous_position()
      const noexcept = 0;

  /**
   * Returns the current velocity of the object.
   *
   * @return the current velocity of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual const Vector2& get_velocity() const noexcept = 0;

  /**
   * Returns the current position of the object.
   *
   * @return the current position of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual const Vector2& get_position() const noexcept = 0;

  /**
   * Returns the interpolated position of the object.
   *
   * @return the interpolated position of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual const Vector2& get_interpolated_position()
      const noexcept = 0;

  /**
   * Returns the calculated next position of the movable object.
   *
   * @param delta the delta time, in seconds.
   * @return the calculated next position of the movable object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual Vector2 get_next_position(
      float delta) const noexcept = 0;
};

static_assert(std::has_virtual_destructor_v<IMovableObject>);

}  // namespace albinjohansson::wanderer