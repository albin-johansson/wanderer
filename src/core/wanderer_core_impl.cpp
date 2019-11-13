#include "wanderer_core_impl.h"

using namespace wanderer::visuals;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl()
    : viewport(Viewport(10, 10, 10, 10)) {

  tileMap = std::make_unique<TileMap>(20, 20);
  player = std::make_unique<Player>();
  player->SetSpeed(400);

  viewport.SetLevelWidth(static_cast<float>(tileMap->GetCols()) * ITile::SIZE);
  viewport.SetLevelHeight(static_cast<float>(tileMap->GetRows()) * ITile::SIZE);
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::HandleInput(const Input& input) {
  player->HandleInput(input);
}

void WandererCoreImpl::Update(float delta) {
  SavePositions();
  player->Tick(delta);
  UpdateViewport();
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
  Interpolate(alpha);

  renderer.SetColor(0, 0, 0);
  renderer.Clear();

  tileMap->Draw(renderer, viewport);
  player->Draw(renderer, viewport);

  renderer.Present();
}

void WandererCoreImpl::SavePositions() {
  player->SavePosition();
}

void WandererCoreImpl::Interpolate(float alpha) {
  player->Interpolate(alpha);
}

void WandererCoreImpl::UpdateViewport() {
  auto interpolatedPosition = player->GetInterpolatedPosition();
  viewport.Track(interpolatedPosition.GetX(),
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

void WandererCoreImpl::SetViewportWidth(float width) {
  viewport.SetWidth(width);
}

void WandererCoreImpl::SetViewportHeight(float height) {
  viewport.SetHeight(height);
}

}