#pragma once
#include "movable_object.h"
#include "animated.h"
#include "level.h"
#include <memory>

namespace albinjohansson::wanderer {

// TODO merchant, citizen, wizard, orc

/**
 * The IEntity interface is a subinterface of IMovableObject that specifies objects that are
 * "alive" in the game world.
 *
 * @see IMovableObject
 * @see IAnimated
 * @since 0.1.0
 */
class IEntity : public virtual IMovableObject, public virtual IAnimated {
 protected:
  IEntity() = default;

 public:
  ~IEntity() override = default;

  /**
   * Hurts the entity by the supplied damage amount.
   *
   * @param dmg the amount of damage that will be inflicted upon the entity.
   * @since 0.1.0
   */
  virtual void Hurt(int dmg) noexcept = 0;

  /**
   * Returns the health of the entity.
   *
   * @return the health of the entity.
   * @since 0.1.0
   */
  [[nodiscard]] virtual int GetHealth() const noexcept = 0;

  /**
   * Indicates whether or not the entity is dead.
   *
   * @return true if the entity is dead; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] virtual bool IsDead() const noexcept = 0;

};

using IEntity_uptr = std::unique_ptr<IEntity>;
using IEntity_sptr = std::shared_ptr<IEntity>;
using IEntity_wptr = std::weak_ptr<IEntity>;

}
