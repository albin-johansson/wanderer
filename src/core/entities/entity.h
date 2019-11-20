#pragma once
#include "movable_object.h"
#include "animated.h"
#include <memory>

namespace wanderer::core {

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

  // TODO GetHealth, Hurt, IsDead, IsAlive
};

using IEntity_uptr = std::unique_ptr<IEntity>;
using IEntity_sptr = std::shared_ptr<IEntity>;
using IEntity_wptr = std::weak_ptr<IEntity>;

}
