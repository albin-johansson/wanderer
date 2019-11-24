#pragma once
#include "entity_state_machine.h"
#include "entity_state.h"
#include "entity_state_id.h"
#include "entity.h"
#include "objects.h"
#include <map>
#include <memory>

namespace albinjohansson::wanderer {

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

  void Tick(const ILevel& level, float delta) final {
    states.at(activeStateID)->Tick(level, delta);
  }

  void Draw(Renderer& renderer, const Viewport& viewport) const final {
    states.at(activeStateID)->Draw(renderer, viewport);
  }

  void SetState(EntityStateID id, const ILevel& level) final {
    states.at(activeStateID)->Exit(level);
    activeStateID = id;
    states.at(activeStateID)->Enter(level);
  }

  [[nodiscard]] IEntity& GetEntity() final { return *entity; }

};

}
