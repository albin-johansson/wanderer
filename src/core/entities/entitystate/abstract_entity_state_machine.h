#pragma once
#include "entity_state_machine.h"
#include "entity_state.h"
#include "entity_state_id.h"
#include "entity.h"
#include "objects.h"
#include <map>
#include <memory>

namespace wanderer::core {

template<class T>
class AbstractEntityStateMachine : public virtual IEntityStateMachine {
 private:
  IEntity* entity = nullptr;
  EntityStateID activeStateID = EntityStateID::IDLE;
  std::map<EntityStateID, std::unique_ptr<T>> states;

 protected:
  explicit AbstractEntityStateMachine(IEntity* entity) {
    this->entity = Objects::RequireNonNull(entity);
  }

  void Put(EntityStateID id, std::unique_ptr<T> state) {
    states.insert(std::pair<EntityStateID, std::unique_ptr<T>>(id, std::move(state)));
  }

  [[nodiscard]] EntityStateID GetActiveStateID() const noexcept { return activeStateID; }

  [[nodiscard]] T& GetActiveState() { return *states.at(activeStateID); }

 public:
  ~AbstractEntityStateMachine() override = default;

  void Tick(const IGame& game, float delta) final {
    states.at(activeStateID)->Tick(game, delta);
  }

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const final {
    states.at(activeStateID)->Draw(renderer, viewport);
  }

  void SetState(EntityStateID id, const IGame& game) final {
    states.at(activeStateID)->Exit(game);
    activeStateID = id;
    states.at(activeStateID)->Enter(game);
  }

  [[nodiscard]] IEntity& GetEntity() final { return *entity; }

};

}
