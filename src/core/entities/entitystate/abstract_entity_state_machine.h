#pragma once
#include "entity_state_machine.h"
#include "entity_state.h"
#include "entity_state_id.h"
#include "objects.h"
#include "entity.h"
#include <unordered_map>
#include <memory>

namespace albinjohansson::wanderer {

/**
 * The AbstractEntityStateMachine class is an abstract class that serves as the base class for
 * all entity-related state machines. The class implements the IEntityStateMachine interface.
 *
 * @see IEntityStateMachine
 * @see IEntityState
 * @tparam T the type of the entity states. By default, the type is IEntityState.
 * @since 0.1.0
 */
template<class T = IEntityState>
class AbstractEntityStateMachine : public virtual IEntityStateMachine {
 private:
  IEntity* entity = nullptr;
  std::unordered_map<EntityStateID, std::unique_ptr<T>> states;
  EntityStateID activeStateID = EntityStateID::IDLE;

 protected:
  /**
   * @param entity a raw pointer to the associated entity instance.
   * @throws NullPointerException if the supplied entity pointer is null.
   * @since 0.1.0
   */
  explicit AbstractEntityStateMachine(IEntity* entity) {
    this->entity = Objects::RequireNonNull(entity);
  }

  /**
   * Attempts to register an entity state ID with an entity state.
   *
   * @param id the ID that will be associated with the state.
   * @param state a unique pointer to the state, mustn't be null!
   * @since 0.1.0
   */
  void Put(EntityStateID id, std::unique_ptr<T>&& state) {
    states.emplace(id, std::move(state));
  }

  /**
   * Returns the currently active state.
   *
   * @return the currently active state.
   * @since 0.1.0
   */
  [[nodiscard]] T& GetActiveState() { return *states.at(activeStateID); }

 public:
  ~AbstractEntityStateMachine() override = default;

  void Tick(const IWandererCore& core, float delta) final {
    states.at(activeStateID)->Tick(core, delta);
  }

  void Draw(Renderer& renderer, const Viewport& viewport) const final {
    states.at(activeStateID)->Draw(renderer, viewport);
  }

  void SetState(EntityStateID id, const IWandererCore& core) final {
    states.at(activeStateID)->Exit(core);
    activeStateID = id;
    states.at(activeStateID)->Enter(core);
  }

  [[nodiscard]] IEntity& GetEntity() final { return *entity; }

};

}
