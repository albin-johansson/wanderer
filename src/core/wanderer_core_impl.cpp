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

  player = std::make_shared<PlayerImpl>(imageGenerator.load("resources/img/player2.png"));

  world = TiledMapParser::Load(imageGenerator, "resources/map/world/world_demo.tmx");
  world->set_player(player);

  activeMap = world;

  const auto[playerX, playerY] = activeMap->get_player_spawn_position();
  player->set_x(playerX);
  player->set_y(playerY);

  init_viewport();

  activeMap->tick(*this, viewport, 0); // needed for first render iteration
}

WandererCoreImpl::~WandererCoreImpl() = default;

void WandererCoreImpl::init_viewport() {
  // TODO listener for viewport dimensions
  viewport.set_level_width(static_cast<float>(activeMap->get_width()));
  viewport.set_level_height(static_cast<float>(activeMap->get_height()));
  viewport.set_width(gameLogicalWidth);
  viewport.set_height(gameLogicalHeight);

  viewport.center(player->get_x(),
                  player->get_y(),
                  Area{player->get_width(), player->get_height()});
}

void WandererCoreImpl::handle_input(const Input& input) {
  menuStateMachine->handle_input(input);
  if (!menuStateMachine->get_menu().is_blocking()) {
    player->handle_input(input, *this);
  }
}

void WandererCoreImpl::update(float delta) {
  if (!menuStateMachine->get_menu().is_blocking()) {
    activeMap->tick(*this, viewport, delta);

    const auto[ix, iy] = player->get_interpolated_position();
    viewport.track(ix, iy, Area{player->get_width(), player->get_height()}, delta);
  }
}

void WandererCoreImpl::render(centurion::Renderer& renderer, float alpha) {
  renderer.set_translation_viewport(viewport);

  activeMap->draw(renderer, viewport, alpha);
  hud.draw(renderer, *this);
  menuStateMachine->draw(renderer, viewport);
}

void WandererCoreImpl::set_viewport_width(float width) {
  viewport.set_width(width);
}

void WandererCoreImpl::set_viewport_height(float height) {
  viewport.set_height(height);
}

void WandererCoreImpl::quit() noexcept {
  shouldQuit = true;
}

void WandererCoreImpl::play_sound(const std::string& id) const {
  soundEngine->play(id);
}

void WandererCoreImpl::set_map(std::shared_ptr<ITileMap> map) {
  if (map) {
    activeMap = map;

    const auto[px, py] = map->get_player_spawn_position();
    player->set_x(px);
    player->set_y(py);

    viewport.set_level_width(static_cast<float>(map->get_width()));
    viewport.set_level_height(static_cast<float>(map->get_height()));
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