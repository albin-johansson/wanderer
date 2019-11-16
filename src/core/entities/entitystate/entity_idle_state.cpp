#include "entity_idle_state.h"
#include "entity_state_machine.h"
#include "entity_sheet.h"

namespace wanderer::core {

EntityIdleState::EntityIdleState(IEntity* entity, IEntityStateMachine* parent)
    : AbstractEntityState(entity, parent) {}

EntityIdleState::~EntityIdleState() = default;

void EntityIdleState::Draw(visuals::Renderer& renderer, const Viewport& viewport) noexcept {
  float srcY = EntitySheet::GetSourceY(512, entity->GetDominantDirection());
  drawDelegate.Draw(renderer, viewport, *entity, 0, srcY);
}

void EntityIdleState::HandleInput(const Input& input) {
  if (input.IsPressed(SDL_SCANCODE_D)
      || input.IsPressed(SDL_SCANCODE_A)
      || input.IsPressed(SDL_SCANCODE_W)
      || input.IsPressed(SDL_SCANCODE_S)) {
    parent->Change(EntityStateID::WALK);
  } else if (input.IsPressed(SDL_SCANCODE_SPACE)) {
    parent->Change(EntityStateID::ATTACK);
  } else if (input.IsPressed(SDL_SCANCODE_U)) {
    parent->Change(EntityStateID::DIE);
  }

  // TODO attack...
}

void EntityIdleState::Tick(float delta) {
}

void EntityIdleState::Enter() {
}

void EntityIdleState::Exit() {
}

}
