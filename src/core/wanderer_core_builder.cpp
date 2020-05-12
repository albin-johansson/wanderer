#include "wanderer_core_builder.h"

#include "action_parser.h"
#include "menu_impl.h"
#include "menu_state_machine_impl.h"
#include "player_impl.h"
#include "tile_map.h"
#include "tiled_map_parser.h"
#include "wanderer_core_impl.h"

using namespace centurion;

namespace albinjohansson::wanderer {

Shared<IWandererCore> WandererCoreBuilder::build(TextureLoader& textureLoader)
{
  auto core = std::shared_ptr<WandererCoreImpl>(new WandererCoreImpl{});

  core->m_menuStateMachine = std::make_shared<MenuStateMachineImpl>();

  ActionParser actionParser{core, core->m_menuStateMachine};

  const auto addMenu = [&](MenuID menu, std::string fileName) {
    const auto path = "resources/menu/" + fileName;
    core->m_menuStateMachine->add_menu(
        menu, std::make_unique<MenuImpl>(actionParser, path.c_str()));
  };

  // TODO load menus
  addMenu(MenuID::Home, "home_menu.json");
  addMenu(MenuID::Settings, "settings_menu.json");
  addMenu(MenuID::Controls, "controls_menu.json");
  addMenu(MenuID::InGame, "in_game_menu.json");

  core->m_soundEngine =
      std::make_unique<SoundEngine>("resources/audio/sfx.txt");

  core->m_player = std::make_shared<PlayerImpl>(
      textureLoader.shared_img("resources/img/player2.png"));

  core->m_world =
      TiledMapParser::load(textureLoader, "resources/map/world/world_demo.tmx");
  core->m_world->set_player(core->m_player);

  core->m_activeMap = core->m_world;

  const auto [playerX, playerY] =
      core->m_activeMap->get_player_spawn_position();
  core->m_player->set_x(playerX);
  core->m_player->set_y(playerY);

  // TODO listener for viewport dimensions
  core->m_viewport.set_level_width(
      static_cast<float>(core->m_activeMap->get_width()));
  core->m_viewport.set_level_height(
      static_cast<float>(core->m_activeMap->get_height()));
  core->m_viewport.set_width(GameConstants::logical_width);
  core->m_viewport.set_height(GameConstants::logical_height);

  core->m_viewport.center(
      core->m_player->get_x(),
      core->m_player->get_y(),
      Area{core->m_player->get_width(), core->m_player->get_height()});

  core->m_activeMap->tick(
      *core, core->m_viewport, 0);  // needed for first render iteration

  return core;
}

}  // namespace albinjohansson::wanderer
