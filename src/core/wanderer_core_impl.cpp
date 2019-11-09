#include "wanderer_core_impl.h"

using namespace wanderer::view;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl() {
  player = std::make_unique<Player>();
  player->SetSpeed(400);
//  player->Move(Direction::RIGHT);
//  player->Move(Direction::DOWN);
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::Update() {
  player->Tick(TIME_STEP);
}

void WandererCoreImpl::Render(Renderer& renderer) {
  renderer.SetColor(0, 0, 0);
  renderer.Clear();

  player->Draw(renderer);

  renderer.Present();
}

void WandererCoreImpl::SavePositions() {
  player->SavePosition();
}

void WandererCoreImpl::Interpolate(double alpha) {
  player->Interpolate(alpha);
}

void WandererCoreImpl::MovePlayer(Direction direction) {
  player->Move(direction);
}

void WandererCoreImpl::StopPlayer(Direction direction) {
  player->Stop(direction);
}

}