#pragma once
#include "sortable_drawable.h"
#include <cstdint>
#include <vector_2.h>

namespace albinjohansson::wanderer {

class IWandererCore;
class Hitbox;
class FRectangle;

/**
 * The IGameObject interface specifies the common interface for all game objects that are present
 * in the game.
 *
 * @see IDrawable
 * @since 0.1.0
 */
class IGameObject : public virtual ISortableDrawable {
 public:
  ~IGameObject() override = default;

  /**
   * Updates the state of the game object. This method should save the position of the object
   * if the object is movable.
   *
   * @param core a reference to the associated wanderer core instance.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void Tick(IWandererCore& core, float delta) = 0;

  virtual void AddHitbox(const FRectangle& rectangle, const Vector2& offset) = 0;

  /**
   * Sets whether or not the game object can block other game objects.
   *
   * @param blocked true if the object is blocking; false otherwise.
   * @since 0.1.0
   */
  virtual void SetBlocked(bool blocked) noexcept = 0;

  /**
   * Returns the x-coordinate of the object.
   *
   * @return the x-coordinate of the object.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual float GetX() const noexcept = 0;

  /**
   * Returns the y-coordinate of the object.
   *
   * @return the y-coordinate of the object.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual float GetY() const noexcept = 0;

  /**
   * Returns the width of the object.
   *
   * @return the width of the object.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual float GetWidth() const noexcept = 0;

  /**
   * Returns the height of the object.
   *
   * @return the height of the object.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual float GetHeight() const noexcept = 0;

  /**
   * Returns the hitbox of the object.
   *
   * @return the hitbox of the object.
   * @since 0.1.0
   */
  [[nodiscard]]
  virtual const Hitbox& GetHitbox() const noexcept = 0;

  [[nodiscard]]
  virtual uint64_t GetUniqueID() const noexcept = 0;

};

}