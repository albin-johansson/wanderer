#pragma once
#include "movable_object.h"
#include "animated.h"
#include <memory>

namespace albinjohansson::wanderer {

/**
 * The IEntity interface is a subinterface of IMovableObject that specifies objects that are
 * "alive" in the game world.
 *
 * @see IMovableObject
 * @see IAnimated
 * @since 0.1.0
 */
class IEntity : public IMovableObject, public IAnimated {
 protected:
  IEntity() = default;

 public:
  ~IEntity() override = default;

  virtual void Hurt(int dmg) noexcept = 0;

  [[nodiscard]] virtual int GetHealth() const noexcept = 0;

  [[nodiscard]] virtual bool IsDead() const noexcept = 0;
};

using IEntity_uptr = std::unique_ptr<IEntity>;
using IEntity_sptr = std::shared_ptr<IEntity>;
using IEntity_wptr = std::weak_ptr<IEntity>;

}
