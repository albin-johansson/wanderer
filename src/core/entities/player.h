#pragma once
#include "entity.h"

namespace albinjohansson::wanderer {

class Input;

class IPlayer : public virtual IEntity {
 protected:
  IPlayer() = default;

 public:
  ~IPlayer() override = default;

  virtual void HandleInput(const Input& input, const IWandererCore& core) = 0;
};

}