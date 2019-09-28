#include "model_impl.h"

namespace wanderer::model {

ModelImpl::ModelImpl() {
  world = std::make_unique<World>();
}

void ModelImpl::Update(double delta) {
  world->Update(delta);
}

Player_sptr ModelImpl::GetPlayer() {
  return world->GetPlayer();
}

void ModelImpl::MovePlayer(Direction direction) {
  world->GetPlayer()->Move(direction);
}

void ModelImpl::StopPlayer(Direction direction) {
  world->GetPlayer()->Stop(direction);
}

} // namespace wanderer::model