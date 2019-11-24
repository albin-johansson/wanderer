#include "abstract_level.h"
#include "objects.h"
#include <algorithm>
#include "skeleton.h"

namespace albinjohansson::wanderer {

AbstractLevel::AbstractLevel(IPlayer_sptr player,
                             SoundEngine_sptr soundEngine,
                             ImageGenerator& imageGenerator) {
  this->player = Objects::RequireNonNull(std::move(player));
  this->soundEngine = Objects::RequireNonNull(std::move(soundEngine));
  tileMap = TileMap::Create(imageGenerator, 25, 25);

  IEntity_sptr skeleton =
      std::make_shared<Skeleton>(imageGenerator.Load("resources/img/skeleton.png"));
  skeleton->SetSpeed(200);
  skeleton->SetX(700);
  skeleton->SetY(500);

  entities.reserve(10);
  entities.push_back(this->player);
  entities.push_back(skeleton);
}

AbstractLevel::~AbstractLevel() = default;

void AbstractLevel::Interpolate(float alpha) {
  for (auto& entity : entities) {
    entity->Interpolate(alpha);
  }
}

void AbstractLevel::Update(float delta) {
  for (auto& entity : entities) {
    entity->SavePosition(); // TODO don't update entities too far away?
    entity->Tick(*this, delta);
  }
}

void AbstractLevel::Render(Renderer& renderer, const Viewport& viewport, float alpha) {
  Interpolate(alpha);

  tileMap->Draw(renderer, viewport);

  std::sort(entities.begin(), entities.end(), AbstractLevel::CompareGameObjects);

  for (auto& entity : entities) {
    entity->Draw(renderer, viewport);
  }
}

void AbstractLevel::PlaySound(const std::string& name) const {
  soundEngine->Play(name);
}

int AbstractLevel::GetTile(int row, int col) {
  return 0; // TODO
}

int AbstractLevel::GetWidth() const noexcept {
  return tileMap->GetWidth();
}

int AbstractLevel::GetHeight() const noexcept {
  return tileMap->GetHeight();
}

const IPlayer& AbstractLevel::GetPlayer() const noexcept {
  return *player;
}

bool AbstractLevel::CompareGameObjects(const IGameObject_sptr& first,
                                       const IGameObject_sptr& second) noexcept {
  return first->GetY() < second->GetY(); // TODO should use center points
}

}
