#pragma once
#include "entity_state.h"
#include "entity.h"

namespace wanderer::core {

class EntityMoveDelegate final : public IEntityState {
 private:
  IEntity* entity = nullptr;

 public:
  explicit EntityMoveDelegate(IEntity* entity);

  ~EntityMoveDelegate() override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) override;

  void Enter(const IGame& world) override;

  void Exit(const IGame& world) override;

  void Tick(const IGame& game, float delta) override;

  [[nodiscard]] inline IEntity* GetEntity() noexcept { return entity; }
};

}
