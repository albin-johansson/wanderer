#pragma once
#include "entity_state_machine.h"
#include "entity.h"
#include "entity_state_id.h"
#include "entity_state.h"
#include <map>

namespace wanderer::core {

class SkeletonStateMachine final : public IEntityStateMachine {
 private:
  IEntity* entity = nullptr;
  EntityStateID activeStateID;
  std::map<EntityStateID, IEntityState_uptr> states;

  void Put(EntityStateID id, IEntityState_uptr state);

 public:
  explicit SkeletonStateMachine(IEntity* entity);

  ~SkeletonStateMachine() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

  void SetState(EntityStateID id, const IGame& game) override;

  void Tick(const IGame& game, float delta) override;

  IEntity& GetEntity() override;

};

}
