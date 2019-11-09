#pragma once
#include "game_object.h"
#include "movable.h"
#include "direction.h"
#include <memory>

namespace wanderer::core {

class IEntity : public IGameObject, public IMovable {
 protected:
  IEntity() = default;

 public:
  ~IEntity() override = default;
};

using IEntity_uptr = std::unique_ptr<IEntity>;
using IEntity_sptr = std::shared_ptr<IEntity>;
using IEntity_wptr = std::weak_ptr<IEntity>;

}
