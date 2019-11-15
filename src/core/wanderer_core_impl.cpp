#include "wanderer_core_impl.h"
#include "menu_state_machine_impl.h"
#include "objects.h"

using namespace wanderer::visuals;

namespace wanderer::core {

WandererCoreImpl::WandererCoreImpl(visuals::ImageGenerator_sptr imgGenerator)
    : viewport(Viewport(1, 1, 1, 1)) {
  imageGenerator = Objects::RequireNonNull(std::move(imgGenerator));

  menuStateMachine = MenuStateMachineImpl::Create();

  tileMap = TileMap::CreateUnique(imageGenerator, 50, 50);

  player = Player::Create(imageGenerator->Load("resources/player.png"));
  player->SetSpeed(300);

  viewport.SetLevelWidth(static_cast<float>(tileMap->GetCols()) * ITile::SIZE);
  viewport.SetLevelHeight(static_cast<float>(tileMap->GetRows()) * ITile::SIZE);
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::HandleInput(const Input& input) {
  menuStateMachine->HandleInput(input);
  if (!menuStateMachine->IsBlocking()) {
    player->HandleInput(input);
  }
}

void WandererCoreImpl::Update(float delta) {
  if (!menuStateMachine->IsBlocking()) {
    SavePositions();
    player->Tick(delta);
    UpdateViewport();
  }
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
  Interpolate(alpha);
  tileMap->Draw(renderer, viewport);
  player->Draw(renderer, viewport);
  menuStateMachine->Draw(renderer, viewport);
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

const Viewport& WandererCoreImpl::GetViewport() const noexcept {
  return viewport;
}

}