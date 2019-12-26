#include "wanderer_core_impl.h"
#include "renderer.h"
#include "player_impl.h"
#include "tile_map.h"
#include "input.h"
#include "sound_effect.h"
#include "menu_state_machine_impl.h"
#include "menu.h"
#include "tiled_map_parser.h"
#include "image_generator.h"
#include "image.h"
#include "window.h"
#include <fstream>
#include <memory>

namespace albinjohansson::wanderer {

WandererCoreImpl::WandererCoreImpl(ImageGenerator& imageGenerator) {
  // TODO fix "this" parameter
  menuStateMachine = std::make_unique<MenuStateMachineImpl>(this);
  soundEngine = std::make_unique<SoundEngine>();
  LoadSounds();

  player = std::make_shared<PlayerImpl>(imageGenerator.Load("resources/img/player2.png"));
  player->SetSpeed(230);

  TiledMapParser parser(imageGenerator, "resources/map/world/world_demo.tmx");

  world = parser.GetMap();
  world->SetPlayer(player);

  activeMap = world;

  auto[playerX, playerY] = activeMap->GetPlayerSpawnPosition();
  player->SetX(playerX);
  player->SetY(playerY);

  // TODO listener for viewport dimensions
  viewport.SetLevelWidth(static_cast<float>(activeMap->GetWidth()));
  viewport.SetLevelHeight(static_cast<float>(activeMap->GetHeight()));
  viewport.SetWidth(1280); // FIXME hardcoded
  viewport.SetHeight(720); // FIXME hardcoded

  viewport.Center(player->GetX(),
                  player->GetY(),
                  Area{player->GetWidth(), player->GetHeight()});

  activeMap->Tick(*this, viewport, 0); // needed for first render iteration
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::LoadSounds() {
  try {
    std::ifstream infile("resources/audio/sfx.txt");
    std::string line;
    while (std::getline(infile, line)) {
      auto i = line.find(';');
      std::string id = line.substr(0, i);
      std::string path = line.substr(i + 1);
      soundEngine->Register(id, std::make_unique<SoundEffect>(path));
    }
  } catch (std::exception& e) {
    SDL_Log("Failed to load sound effects! Error: %s", e.what());
  }
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

    auto[ix, iy] = player->GetInterpolatedPosition();
    viewport.Center(ix, iy, {player->GetWidth(), player->GetHeight()});
  }
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
  renderer.SetTranslationViewport(viewport);

  activeMap->Draw(renderer, viewport, alpha);
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

    auto[px, py] = map->GetPlayerSpawnPosition();
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