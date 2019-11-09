#include "wanderer_core_impl.h"

using namespace wanderer::view;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl() {
  player = std::make_unique<Player>();
  player->SetSpeed(100);
  player->Move(Direction::RIGHT);
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

void WandererCoreImpl::Interpolate(float alpha) {
  player->Interpolate(alpha);
}

}