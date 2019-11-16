#include "world.h"
#include "objects.h"
#include <utility>

using namespace wanderer::visuals;

namespace wanderer::core {

World::World(visuals::ImageGenerator_sptr imgGen, IEntity_sptr player) {
  this->imageGenerator = Objects::RequireNonNull(std::move(imgGen));
  this->player = Objects::RequireNonNull(std::move(player));
  tileMap = TileMap::Create(imageGenerator, 50, 50);
}

World::~World() = default;

World_uptr World::Create(visuals::ImageGenerator_sptr imgGen, IEntity_sptr player) {
  return std::make_unique<World>(imgGen, player);
}

void World::SavePositions() {
  player->SavePosition();
}

void World::Interpolate(float alpha) {
  player->Interpolate(alpha);
}

void World::Tick(float delta) {
  SavePositions();
  player->Tick(delta);
}

void World::Render(visuals::Renderer& renderer, const Viewport& viewport, float alpha) {
  Interpolate(alpha);
  tileMap->Draw(renderer, viewport);
  player->Draw(renderer, viewport);
}

int World::GetWidth() const noexcept {
  return tileMap->GetWidth();
}

int World::GetHeight() const noexcept {
  return tileMap->GetHeight();
}

}
