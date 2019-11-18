#pragma once
#include "player_state_machine.h"
#include "player_state.h"
#include <memory>
#include <map>
#include "entity.h"

namespace wanderer::core {

class PlayerStateMachineImpl final : public IPlayerStateMachine {
 private:
  std::map<EntityStateID, IPlayerState_uptr> states;
  EntityStateID activeStateID;
  IEntity* entity = nullptr;

  void Put(EntityStateID id, IPlayerState_uptr state);

 public:
  /**
   * @param entity a pointer to the associated entity instance, will not be freed by the created
   * state machine.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit PlayerStateMachineImpl(IEntity* entity);

  ~PlayerStateMachineImpl() override;

  static IPlayerStateMachine_uptr Create(IEntity* entity);

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept override;

  void HandleInput(const Input& input) override;

  void Change(EntityStateID id) override;

  void Tick(float delta) override;
};

}
