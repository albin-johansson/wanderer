#pragma once
#include "tickable.h"
#include "drawable.h"
#include "rectangle.h"
#include <memory>

namespace wanderer::core {

/**
 * The IGameObject interface specifies the common interface for all game objects that are present
 * in the game. Game objects must be be drawable. However, there is no requirement for game
 * objects to do anything in their implementation of the ITickable::Tick(float) method.
 *
 * @see ITickable
 * @see IDrawable
 * @since 0.1.0
 */
class IGameObject : public ITickable, public IDrawable {
 protected:
  IGameObject() = default;

 public:
  ~IGameObject() override = default;

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