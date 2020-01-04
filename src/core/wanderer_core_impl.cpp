#include "wanderer_core_impl.h"
#include "menu_state_machine_impl.h"
#include "player_impl.h"
#include "renderer.h"
#include "tile_map.h"
#include "input.h"
#include "sound_effect.h"
#include "menu.h"
#include "tiled_map_parser.h"
#include "image_generator.h"
#include "image.h"
#include "window.h"
#include "game_constants.h"
#include <memory>

namespace albinjohansson::wanderer {

WandererCoreImpl::WandererCoreImpl(ImageGenerator& imageGenerator) {
  menuStateMachine = std::make_unique<MenuStateMachineImpl>(this);
  soundEngine = std::make_unique<SoundEngine>("resources/audio/sfx.txt");

  player = std::make_shared<PlayerImpl>(imageGenerator.Load("resources/img/player2.png"));

  world = TiledMapParser::Load(imageGenerator, "resources/map/world/world_demo.tmx");
  world->SetPlayer(player);

  activeMap = world;

  const auto[playerX, playerY] = activeMap->GetPlayerSpawnPosition();
  player->SetX(playerX);
  player->SetY(playerY);

  InitViewport();

  activeMap->Tick(*this, viewport, 0); // needed for first render iteration
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::InitViewport() {
  // TODO listener for viewport dimensions
  viewport.SetLevelWidth(static_cast<float>(activeMap->GetWidth()));
  viewport.SetLevelHeight(static_cast<float>(activeMap->GetHeight()));
  viewport.SetWidth(gameLogicalWidth);
  viewport.SetHeight(gameLogicalHeight);

  viewport.Center(player->GetX(),
                  player->GetY(),
                  Area{player->GetWidth(), player->GetHeight()});
}

void WandererCoreImpl::HandleInput(const Input& input) {
  menuStateMachine->HandleInput(input);
  if (!menuStateMachine->GetMenu().IsBlocking()) {
    player->HandleInput(input, *this);
  }
}

void WandererCoreImpl::Update(float delta) {
  if (!menuStateMachine->GetMenu().IsBlocking()) {
    activeMap->Tick(*this, viewport, delta);

    const auto[ix, iy] = player->GetInterpolatedPosition();
    viewport.Track(ix, iy, Area{player->GetWidth(), player->GetHeight()}, delta);
  }
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
  renderer.SetTranslationViewport(viewport);

  activeMap->Draw(renderer, viewport, alpha);
  hud.Draw(renderer, *this);
  menuStateMachine->Draw(renderer, viewport);
}

void WandererCoreImpl::SetViewportWidth(float width) {
  viewport.SetWidth(width);
}

void WandererCoreImpl::SetViewportHeight(float height) {
  viewport.SetHeight(height);
}

void WandererCoreImpl::Quit() noexcept {
  shouldQuit = true;
}

void WandererCoreImpl::PlaySound(const std::string& id) const {
  soundEngine->Play(id);
}

void WandererCoreImpl::SetMap(std::shared_ptr<ITileMap> map) {
  if (map) {
    activeMap = map;

    const auto[px, py] = map->GetPlayerSpawnPosition();
    player->SetX(px);
    player->SetY(py);

    viewport.SetLevelWidth(static_cast<float>(map->GetWidth()));
    viewport.SetLevelHeight(static_cast<float>(map->GetHeight()));
  }
}

bool WandererCoreImpl::ShouldQuit() const noexcept {
  return shouldQuit;
}

const IPlayer& WandererCoreImpl::GetPlayer() const {
  return *player;
}

const ITileMap& WandererCoreImpl::GetActiveMap() const {
  return *activeMap;
}

}