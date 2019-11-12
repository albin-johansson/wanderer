#pragma once
#include "tickable.h"
#include "input.h"
#include "entity.h"
#include <memory>

namespace wanderer::core {

/**
 * The IEntityState interface specifies .
 *
 * @since 0.1.0
 */
class IEntityState {
 protected:
  IEntityState() = default;

 public:
  virtual ~IEntityState() = default;

  virtual void Update(IEntity& entity, float delta) = 0;

  virtual void HandleInput(IEntity& entity, const Input& input) = 0;

  virtual void EnterState(IEntity& entity) = 0;

  virtual void ExitState(IEntity& entity) = 0;

};

using IEntityState_uptr = std::unique_ptr<IEntityState>;
using IEntityState_sptr = std::shared_ptr<IEntityState>;
using IEntityState_wptr = std::weak_ptr<IEntityState>;

}