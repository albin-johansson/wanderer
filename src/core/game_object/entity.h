#pragma once
#include "movable_object.h"
#include <memory>

namespace wanderer::core {

class IEntity : public IMovableObject {
 protected:
  IEntity() = default;

 public:
  ~IEntity() override = default;

  // TODO ...
};

using IEntity_uptr = std::unique_ptr<IEntity>;
using IEntity_sptr = std::shared_ptr<IEntity>;
using IEntity_wptr = std::weak_ptr<IEntity>;

}
