#include "world.h"

namespace wanderer::model {

World::World() {
  activeLevel = nullptr;
  player = std::make_unique<Player>(550, 200, 50, 50);
}

World::~World() = default;

void World::Update(double delta) {
  player->Update(delta);
//  if (activeLevel != nullptr) {
//    activeLevel->Update(delta);
//  }
}

void World::SetLevel(ILevel_sptr level) noexcept {
  this->activeLevel = std::move(level);
}

Player_sptr World::GetPlayer() {
  return player;
}

} // namespace wanderer::model