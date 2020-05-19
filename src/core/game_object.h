#pragma once
#include <rect.h>

#include <type_traits>

#include "sortable_drawable.h"
#include "vector_2.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class IWandererCore;
class Hitbox;

/**
 * The IGameObject interface specifies the common interface for all game objects
 * that are present in the game.
 *
 * @see IDrawable
 * @since 0.1.0
 */
class IGameObject : public virtual ISortableDrawable {
 public:
  ~IGameObject() override = default;

  /**
   * Updates the state of the game object. This method should save the position
   * of the object if the object is movable.
   *
   * @param core a reference to the associated wanderer core instance.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  virtual void tick(IWandererCore& core, float delta) = 0;

  virtual void add_hitbox(const ctn::FRect& rectangle,
                          const Vector2& offset) = 0;

  /**
   * Sets whether or not the game object can block other game objects.
   *
   * @param blocked true if the object is blocking; false otherwise.
   * @since 0.1.0
   */
  virtual void set_blocked(bool blocked) noexcept = 0;

  /**
   * Returns the x-coordinate of the object.
   *
   * @return the x-coordinate of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float get_x() const noexcept = 0;

  /**
   * Returns the y-coordinate of the object.
   *
   * @return the y-coordinate of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float get_y() const noexcept = 0;

  /**
   * Returns the width of the object.
   *
   * @return the width of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float get_width() const noexcept = 0;

  /**
   * Returns the height of the object.
   *
   * @return the height of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual float get_height() const noexcept = 0;

  /**
   * Returns the hitbox of the object.
   *
   * @return the hitbox of the object.
   * @since 0.1.0
   */
  [[nodiscard]] virtual const Hitbox& get_hitbox() const noexcept = 0;

  [[nodiscard]] virtual uint64 get_unique_id() const noexcept = 0;
};

static_assert(std::has_virtual_destructor_v<IGameObject>);

}  // namespace wanderer