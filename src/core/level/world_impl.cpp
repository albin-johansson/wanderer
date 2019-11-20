#include "world_impl.h"
#include "objects.h"
#include "player.h"

using namespace wanderer::visuals;

namespace wanderer::core {

WorldImpl::WorldImpl(visuals::ImageGenerator& imageGenerator) {
  player = Player::Create(imageGenerator.Load("resources/img/player2.png"));
  player->SetSpeed(300);

  tileMap = TileMap::Create(imageGenerator, 50, 50);
}

WorldImpl::~WorldImpl() = default;

IWorld_uptr WorldImpl::Create(visuals::ImageGenerator& imageGenerator) {
  return std::make_unique<WorldImpl>(imageGenerator);
}

void WorldImpl::PlayerHandleInput(const Input& input, const IGame& game) {
  player->HandleInput(input, game);
}

void WorldImpl::SavePositions() {
  player->SavePosition();
}

void WorldImpl::Tick(const IGame& game, float delta) {
  SavePositions();
  player->Tick(game, delta);
}

void WorldImpl::Interpolate(float alpha) {
  player->Interpolate(alpha);
}

void WorldImpl::Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) {
  Interpolate(alpha);
  tileMap->Draw(renderer, viewport);
  player->Draw(renderer, viewport);
}

int WorldImpl::GetWidth() const noexcept {
  return tileMap->GetWidth();
}

int WorldImpl::GetHeight() const noexcept {
  return tileMap->GetHeight();
}

float WorldImpl::GetPlayerWidth() const noexcept {
  return player->GetWidth();
}

float WorldImpl::GetPlayerHeight() const noexcept {
  return player->GetHeight();
}

Vector2 WorldImpl::GetPlayerPosition() const noexcept {
  return player->GetPosition();
}

Vector2 WorldImpl::GetPlayerInterpolatedPosition() const noexcept {
  return player->GetInterpolatedPosition();
}

}
