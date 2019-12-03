#pragma once
#include "entity.h"
#include "input.h"
#include "wanderer_core.h"
#include <memory>

namespace albinjohansson::wanderer {

class IPlayer : public virtual IEntity {
 protected:
  IPlayer() = default;

 public:
  ~IPlayer() override = default;

  virtual void HandleInput(const Input& input, const IWandererCore& core) = 0;
};

using IPlayer_uptr = std::unique_ptr<IPlayer>;
using IPlayer_sptr = std::shared_ptr<IPlayer>;
using IPlayer_wptr = std::weak_ptr<IPlayer>;

}