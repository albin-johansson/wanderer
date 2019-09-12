#include "world.h"

namespace wanderer::model {

World::World() {
  activeLevel = nullptr;
}

World::~World() = default;

void World::Update(double delta) {
  if (activeLevel != nullptr) {
    activeLevel->Update(delta);
  }
}

void World::SetLevel(ILevel_sptr level) noexcept {
  this->activeLevel = std::move(level);
}

} // namespace wanderer::model