#pragma once
#include <memory>
#include <unordered_map>

#include "entity.h"
#include "entity_state.h"
#include "entity_state_id.h"
#include "entity_state_machine.h"
#include "require.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

/**
 * The AbstractEntityStateMachine class is an abstract class that serves as the
 * base class for all entity-related state machines. The class implements the
 * IEntityStateMachine interface.
 *
 * @see IEntityStateMachine
 * @see IEntityState
 * @tparam T the type of the entity states. By default, the type is
 * IEntityState.
 * @since 0.1.0
 */
template <class T = IEntityState>
class AbstractEntityStateMachine : public virtual IEntityStateMachine {
 private:
  IEntity* entity = nullptr;
  std::unordered_map<EntityStateID, Unique<T>> states;
  EntityStateID activeStateID = EntityStateID::Idle;

 protected:
  /**
   * @param entity a raw pointer to the associated entity instance.
   * @throws NullPointerException if the supplied entity pointer is null.
   * @since 0.1.0
   */
  explicit AbstractEntityStateMachine(IEntity* entity)
  {
    this->entity = Require::not_null(entity);
  }

  /**
   * Attempts to register an entity state ID with an entity state.
   *
   * @param id the ID that will be associated with the state.
   * @param state a unique pointer to the state, mustn't be null!
   * @since 0.1.0
   */
  void put(EntityStateID id, Unique<T>&& state)
  {
    states.emplace(id, std::move(state));
  }

  /**
   * Returns the currently active state.
   *
   * @return the currently active state.
   * @since 0.1.0
   */
  [[nodiscard]] T& get_active_state()
  {
    return *states.at(activeStateID);
  }

 public:
  ~AbstractEntityStateMachine() override = default;

  void tick(const IWandererCore& core, float delta) final
  {
    states.at(activeStateID)->tick(core, delta);
  }

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const final
  {
    states.at(activeStateID)->draw(renderer, viewport);
  }

  void set_state(EntityStateID id, const IWandererCore& core) final
  {
    states.at(activeStateID)->exit(core);
    activeStateID = id;
    states.at(activeStateID)->enter(core);
  }

  [[nodiscard]] IEntity& get_entity() final
  {
    return *entity;
  }
};

}  // namespace albinjohansson::wanderer
