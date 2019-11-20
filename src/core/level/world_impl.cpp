#include "world_impl.h"
#include "objects.h"
#include "player.h"
#include <utility>

using namespace wanderer::visuals;

namespace wanderer::core {

WorldImpl::WorldImpl(visuals::ImageGenerator& imageGenerator, Player_sptr player) {
  this->player = Objects::RequireNonNull(std::move(player));
  tileMap = TileMap::Create(imageGenerator, 50, 50);
}

WorldImpl::~WorldImpl() = default;

IWorld_uptr WorldImpl::Create(visuals::ImageGenerator& imageGenerator, Player_sptr player) {
  return std::make_unique<WorldImpl>(imageGenerator, std::move(player));
}

void WorldImpl::SavePositions() {
  player->SavePosition();
}

void WorldImpl::Interpolate(float alpha) {
  player->Interpolate(alpha);
}

void WorldImpl::Tick(const IGame& game, float delta) {
  SavePositions();
  player->Tick(game, delta);
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

}
