#pragma once
#include "drawable.h"
#include "rectangle.h"
#include <memory>

namespace albinjohansson::wanderer {

class ILevel;

/**
 * The IGameObject interface specifies the common interface for all game objects that are present
 * in the game.
 *
 * @see IDrawable
 * @since 0.1.0
 */
class IGameObject : public virtual IDrawable {
 protected:
  IGameObject() = default;

 public:
  ~IGameObject() override = default;

  /**
   * Updates the state of the game object.
   *
   * @param level a reference to the level that the object is located in.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void Tick(ILevel& level, float delta) = 0;

  /**
   * Returns the x-coordinate of the object.
   *
   * @return the x-coordinate of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float GetX() const noexcept = 0;

  /**
   * Returns the y-coordinate of the object.
   *
   * @return the y-coordinate of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float GetY() const noexcept = 0;

  /**
   * Returns the width of the object.
   *
   * @return the width of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float GetWidth() const noexcept = 0;

  /**
   * Returns the height of the object.
   *
   * @return the height of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float GetHeight() const noexcept = 0;

  /**
   * Returns a rectangle that represents the hitbox of the object.
   *
   * @return a rectangle that represents the hitbox of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual Rectangle GetHitbox() const noexcept = 0;
};

using IGameObject_uptr = std::unique_ptr<IGameObject>;
using IGameObject_sptr = std::shared_ptr<IGameObject>;
using IGameObject_wptr = std::weak_ptr<IGameObject>;

}