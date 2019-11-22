#include "world_impl.h"
#include "objects.h"
#include "player.h"
#include "skeleton.h"
#include <algorithm>

using namespace wanderer::visuals;

namespace wanderer::core {

WorldImpl::WorldImpl(visuals::ImageGenerator& imageGenerator) {
  player = Player::Create(imageGenerator.Load("resources/img/player2.png"));
  player->SetSpeed(300);
  player->SetX(1000);
  player->SetY(500);

  IEntity_sptr skeleton =
      std::make_unique<Skeleton>(imageGenerator.Load("resources/img/skeleton.png"));
  skeleton->SetSpeed(200);
  skeleton->SetX(500);
  skeleton->SetY(100);

  tileMap = TileMap::Create(imageGenerator, 50, 50);

  entities.reserve(20);
  entities.push_back(player);
  entities.push_back(skeleton);
}

WorldImpl::~WorldImpl() = default;

IWorld_uptr WorldImpl::Create(visuals::ImageGenerator& imageGenerator) {
  return std::make_unique<WorldImpl>(imageGenerator);
}

void WorldImpl::PlayerHandleInput(const Input& input, const IGame& game) {
  player->HandleInput(input, game);
}

void WorldImpl::SavePositions() {
  for (auto& entity : entities) {
    entity->SavePosition();
  }
}

void WorldImpl::Tick(const IGame& game, float delta) {
  SavePositions();
  for (auto& entity : entities) {
    entity->Tick(game, delta);
  }
}

void WorldImpl::Interpolate(float alpha) {
  for (auto& entity : entities) {
    entity->Interpolate(alpha);
  }
}

void WorldImpl::Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) {
  Interpolate(alpha);
  tileMap->Draw(renderer, viewport);

  std::sort(entities.begin(), entities.end(), WorldImpl::CompareGameObjects);

  for (auto& entity : entities) {
    entity->Draw(renderer, viewport);
  }
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

bool WorldImpl::CompareGameObjects(const IGameObject_sptr& first,
                                   const IGameObject_sptr& second) noexcept {
  return first->GetY() < second->GetY();
}

}