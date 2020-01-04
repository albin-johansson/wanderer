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

namespace albinjohansson::wanderer {

WandererCoreImpl::WandererCoreImpl(ImageGenerator& imageGenerator) {
  menuStateMachine = std::make_unique<MenuStateMachineImpl>(this);
  soundEngine = std::make_unique<SoundEngine>("resources/audio/sfx.txt");

  player = std::make_shared<PlayerImpl>(imageGenerator.Load("resources/img/player2.png"));

  world = TiledMapParser::Load(imageGenerator, "resources/map/world/world_demo.tmx");
  world->SetPlayer(player);

  activeMap = world;

  const auto[playerX, playerY] = activeMap->GetPlayerSpawnPosition();
  player->set_x(playerX);
  player->set_y(playerY);

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

  viewport.Center(player->get_x(),
                  player->get_y(),
                  Area{player->get_width(), player->get_height()});
}

void WandererCoreImpl::handle_input(const Input& input) {
  menuStateMachine->HandleInput(input);
  if (!menuStateMachine->GetMenu().IsBlocking()) {
    player->HandleInput(input, *this);
  }
}

void WandererCoreImpl::update(float delta) {
  if (!menuStateMachine->GetMenu().IsBlocking()) {
    activeMap->Tick(*this, viewport, delta);

    const auto[ix, iy] = player->get_interpolated_position();
    viewport.Track(ix, iy, Area{player->get_width(), player->get_height()}, delta);
  }
}

void WandererCoreImpl::render(centurion::Renderer& renderer, float alpha) {
  renderer.SetTranslationViewport(viewport);

  activeMap->Draw(renderer, viewport, alpha);
  hud.Draw(renderer, *this);
  menuStateMachine->Draw(renderer, viewport);
}

void WandererCoreImpl::set_viewport_width(float width) {
  viewport.SetWidth(width);
}

void WandererCoreImpl::set_viewport_height(float height) {
  viewport.SetHeight(height);
}

void WandererCoreImpl::quit() noexcept {
  shouldQuit = true;
}

void WandererCoreImpl::play_sound(const std::string& id) const {
  soundEngine->Play(id);
}

void WandererCoreImpl::set_map(std::shared_ptr<ITileMap> map) {
  if (map) {
    activeMap = map;

    const auto[px, py] = map->GetPlayerSpawnPosition();
    player->set_x(px);
    player->set_y(py);

    viewport.SetLevelWidth(static_cast<float>(map->GetWidth()));
    viewport.SetLevelHeight(static_cast<float>(map->GetHeight()));
  }
}

bool WandererCoreImpl::should_quit() const noexcept {
  return shouldQuit;
}

const IPlayer& WandererCoreImpl::get_player() const {
  return *player;
}

const ITileMap& WandererCoreImpl::get_active_map() const {
  return *activeMap;
}

}