#include "wanderer_core_impl.h"

using namespace wanderer::visuals;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl()
    : viewport(Viewport(1500, 800, 2000, 2000)) {

  tileMap = std::make_unique<TileMap>(10, 10);
  player = std::make_unique<Player>();
  player->SetSpeed(400);

}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::Update() {
  player->Tick(TIME_STEP);
}

void WandererCoreImpl::Render(Renderer& renderer) {
  renderer.SetColor(0, 0, 0);
  renderer.Clear();

  viewport.Center(player->GetX(), player->GetY(), player->GetWidth(), player->GetHeight());

  tileMap->Draw(renderer, viewport);
  player->Draw(renderer, viewport);

  renderer.Present();
}

void WandererCoreImpl::SavePositions() {
  player->SavePosition();
}

void WandererCoreImpl::Interpolate(double alpha) {
  player->Interpolate(static_cast<float>(alpha)); // TODO only use floats or doubles
}

void WandererCoreImpl::MovePlayer(Direction direction) {
  player->Move(direction);
}

void WandererCoreImpl::StopPlayer(Direction direction) {
  player->Stop(direction);
}

}