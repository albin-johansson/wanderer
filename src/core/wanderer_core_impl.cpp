#include "wanderer_core_impl.h"
#include "menu_state_machine_impl.h"
#include "player_impl.h"
#include "tiled_map_parser.h"
#include <fstream>
#include <memory>

namespace albinjohansson::wanderer {

WandererCoreImpl::WandererCoreImpl(ImageGenerator& imageGenerator) {
  menuStateMachine = MenuStateMachineImpl::Create(this); // TODO fix "this" parameter
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
                  {player->GetWidth(), player->GetHeight()});
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
      soundEngine->Register(id, SoundEffect::Create(path));
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
    viewport.Track(ix, iy, {player->GetWidth(), player->GetHeight()}, delta);
  }
}

void WandererCoreImpl::Render(Renderer& renderer, float alpha) {
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
  if (map != nullptr) {
    activeMap = map;

    auto[px, py] = map->GetPlayerSpawnPosition();
    player->SetX(px);
    player->SetY(py);

    viewport.SetLevelWidth(static_cast<float>(map->GetWidth()));
    viewport.SetLevelHeight(static_cast<float>(map->GetHeight()));
  }
}

}