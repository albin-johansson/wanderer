#include "wanderer_core_impl.h"

using namespace wanderer::visuals;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl()
    : viewport(Viewport(10, 10, 10, 10)) {

  tileMap = std::make_unique<TileMap>(10, 10);
  player = std::make_unique<Player>();
  player->SetSpeed(400);

  viewport.SetLevelWidth(tileMap->GetCols() * Tile::SIZE);
  viewport.SetLevelHeight(tileMap->GetRows() * Tile::SIZE);
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::Update() {
  player->Tick(TIME_STEP);
}

void WandererCoreImpl::Render(Renderer& renderer) {
  renderer.SetColor(0, 0, 0);
  renderer.Clear();

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

void WandererCoreImpl::UpdateViewport() {
  auto interpolatedPosition = player->GetInterpolatedPosition();
  viewport.Center(interpolatedPosition.GetX(),
                  interpolatedPosition.GetY(),
                  player->GetWidth(),
                  player->GetHeight());
}

void WandererCoreImpl::MovePlayer(Direction direction) {
  player->Move(direction);
}

void WandererCoreImpl::StopPlayer(Direction direction) {
  player->Stop(direction);
}

void WandererCoreImpl::SetViewportWidth(int width) {
  viewport.SetWidth(width);
}

void WandererCoreImpl::SetViewportHeight(int height) {
  viewport.SetHeight(height);
}

}