#include "game.hpp"

#include "components/ctx/renderer_snapshot.hpp"
#include "components/ctx/settings.hpp"
#include "components/items/inventory.hpp"
#include "components/ui/fps_data.hpp"
#include "core/ecs/event_connections.hpp"
#include "core/ecs/make_dispatcher.hpp"
#include "core/ecs/registry_utils.hpp"
#include "events/load_game_event.hpp"
#include "events/menu_events.hpp"
#include "io/maps/load_levels.hpp"
#include "io/saves/delete_save.hpp"
#include "io/saves/load/load_game.hpp"
#include "io/saves/save/save_game.hpp"
#include "systems/ai/chase_system.hpp"
#include "systems/ai/humanoid/humanoid_animation_system.hpp"
#include "systems/ai/humanoid/humanoid_state_system.hpp"
#include "systems/ai/roam_system.hpp"
#include "systems/animation/animation_system.hpp"
#include "systems/animation/custom_animation_system.hpp"
#include "systems/animation/tile_animation_system.hpp"
#include "systems/animation/tile_object_animation_system.hpp"
#include "systems/configuration/load_binds_system.hpp"
#include "systems/configuration/settings_system.hpp"
#include "systems/gfx/debug_rendering_system.hpp"
#include "systems/gfx/depth_system.hpp"
#include "systems/gfx/drawable_system.hpp"
#include "systems/gfx/light_system.hpp"
#include "systems/gfx/render_bounds_system.hpp"
#include "systems/gfx/tile_layer_rendering_system.hpp"
#include "systems/gfx/viewport_system.hpp"
#include "systems/input/input_system.hpp"
#include "systems/levels/level_system.hpp"
#include "systems/physics/movement_system.hpp"
#include "systems/physics/particle_system.hpp"
#include "systems/plant_system.hpp"
#include "systems/registry_system.hpp"
#include "systems/time_system.hpp"
#include "systems/trigger_system.hpp"
#include "systems/ui/fps_system.hpp"
#include "systems/ui/hud/hud_rendering_system.hpp"
#include "systems/ui/hud/level_switch_animation_system.hpp"
#include "systems/ui/menus/menu_rendering_system.hpp"
#include "systems/ui/menus/menu_system.hpp"
#include "systems/ui/menus/saves/saves_menu_system.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

Game::Game(graphics_type& graphics)
    : m_shared{sys::MakeSharedRegistry()}
    , m_dispatcher{MakeDispatcher()}
{
  LoadLevels(m_shared, graphics);

  // clang-format off
  m_dispatcher.sink<SwitchMapEvent>().connect<&Game::on_switch_map>(this);
  m_dispatcher.sink<switch_menu_event>().connect<&Game::on_switch_menu>(this);
  m_dispatcher.sink<menu_switched_event>().connect<&Game::on_menu_switched>(this);
  m_dispatcher.sink<button_pressed_event>().connect<&Game::on_button_pressed>(this);

  m_dispatcher.sink<ShowInventoryEvent>().connect<&Game::on_show_inventory>(this);
  m_dispatcher.sink<CloseInventoryEvent>().connect<&Game::on_close_inventory>(this);

  m_dispatcher.sink<SleepEvent>().connect<&Game::on_sleep>(this);
  m_dispatcher.sink<DayChangedEvent>().connect<&Game::on_day_changed>(this);

  m_dispatcher.sink<CustomAnimationHalfwayEvent>().connect<&Game::on_custom_animation_halfway>(this);

  m_dispatcher.sink<SpawnParticlesEvent>().connect<&Game::on_spawn_particles>(this);
  m_dispatcher.sink<QuitEvent>().connect<&Game::on_quit>(this);
  // clang-format on
}

Game::~Game()
{
  DisconnectEvents(m_dispatcher);
  m_dispatcher.disconnect(this);
}

void Game::on_start()
{
  sys::LoadSettings(m_shared);
  m_shared.set<ctx::Binds>(sys::LoadBinds());
  m_shared.ctx<ctx::TimeOfDay>().seconds = sys::HourToSeconds(12);

  {
    auto& data = m_shared.emplace<comp::FpsData>(m_shared.create());
    data.then = cen::counter::ticks();
    data.interval = ms_t{500};
    data.next_update = data.then + data.interval;
  }

  const auto& settings = m_shared.ctx<ctx::Settings>();
  m_dispatcher.enqueue<fullscreen_toggled_event>(settings.fullscreen);
  m_dispatcher.enqueue<integer_scaling_toggled_event>(settings.integer_scaling);

  sys::SyncSettingsMenu(m_shared);
  m_dispatcher.update();
}

void Game::on_exit()
{
  sys::SaveSettingsBeforeExit(m_shared);
}

void Game::handle_input(const rune::input& input)
{
  m_mousePos = input.mouse.position();
  sys::UpdateMenu(m_shared, m_dispatcher, input);

  auto& level = sys::CurrentLevel(m_shared);
  sys::UpdateInput(level.registry, m_dispatcher, input, m_shared.ctx<ctx::Binds>());
}

void Game::tick(const float dt)
{
  m_dispatcher.update();

  auto& level = sys::CurrentLevel(m_shared);
  sys::UpdateFps(m_shared, dt);

  sys::UpdateRenderBounds(level.registry);
  sys::UpdateCustomAnimations(level.registry, m_dispatcher, dt);

  if (is_paused()) {
    return;
  }

  sys::UpdateTime(m_shared, m_dispatcher, dt);
  sys::UpdateHumanoidStates(level.registry, m_dispatcher);

  sys::UpdateChase(level.registry);
  sys::UpdateRoaming(level.registry, dt);
  sys::UpdateMovement(level.registry, level.tree, dt);
  sys::UpdateDrawables(level.registry);
  sys::UpdateParticles(level.registry, dt);
  sys::UpdatePlants(level.registry, dt);
  sys::UpdateLights(level.registry);
  sys::UpdatePlayerLightPosition(level.registry);
  sys::UpdateTriggers(level.registry);

  {
    const auto player = singleton_entity<comp::Player>(level.registry);
    sys::UpdateViewport(level.registry, player, dt);
  }
  sys::UpdateDepth(level.registry);

  sys::UpdateAnimations(level.registry);
  sys::UpdateHumanoidAnimations(level.registry);
  sys::UpdateTileAnimations(level.registry);
  sys::UpdateTileObjectAnimations(level.registry);
}

void Game::render(graphics_type& graphics) const
{
  m_shared.set<ref<GraphicsContext>>(graphics);

  auto& level = sys::CurrentLevel(m_shared);
  level.registry.set<ref<GraphicsContext>>(graphics);

  auto& renderer = graphics.get_renderer();
  renderer.clear_with(cen::colors::black);

  sys::TranslateViewport(level.registry);

  sys::RenderTileLayers(level.registry);
  sys::RenderDrawables(level.registry);
  sys::RenderParticles(level.registry);

  if (sys::IsCurrentLevelOutside(m_shared)) {
    sys::RenderLights(level.registry, m_shared.ctx<ctx::TimeOfDay>());
  }

  sys::RenderClock(m_shared);

  if (m_updateSnapshot) {
    m_shared.set<ctx::RendererSnapshot>(renderer.capture(graphics.format()));
    m_updateSnapshot = false;
  }

  if constexpr (cen::is_debug_build()) {
    sys::RenderDebugInfo(level.registry);
  }

  sys::RenderHud(m_shared, m_mousePos);

  sys::RenderActiveMenu(m_shared);
  sys::RenderCustomAnimations(level.registry);

  sys::RenderFps(m_shared);

  if constexpr (cen::is_debug_build()) {
    sys::RenderMenuDebugInfo(m_shared);
  }

  renderer.present();

  /* Let's embrace our paranoia and unset the renderer context variables! */
  level.registry.unset<ref<GraphicsContext>>();
  m_shared.unset<ref<GraphicsContext>>();
}

void Game::load_save(const std::string& name, graphics_type& graphics)
{
  LoadGame(m_shared, graphics, name);

  auto& level = sys::CurrentLevel(m_shared);
  sys::StartBondAnimation(level.registry, glob::load_game_id);
}

auto Game::is_paused() const -> bool
{
  return sys::IsCurrentMenuBlocking(m_shared);
}

void Game::on_button_pressed(const button_pressed_event& event)
{
  switch (event.action) {
    default:
      [[fallthrough]];
    case MenuAction::None:
      break;

    case MenuAction::GotoInGame: {
      m_dispatcher.enqueue<switch_menu_event>(MenuId::InGame);
      break;
    }
    case MenuAction::GotoHome: {
      m_updateSnapshot = true;
      m_dispatcher.enqueue<switch_menu_event>(MenuId::Home);
      break;
    }
    case MenuAction::GotoControls: {
      m_dispatcher.enqueue<switch_menu_event>(MenuId::Controls);
      break;
    }
    case MenuAction::GotoSettings: {
      m_dispatcher.enqueue<switch_menu_event>(MenuId::Settings);
      break;
    }
    case MenuAction::GotoSaves: {
      m_dispatcher.enqueue<switch_menu_event>(MenuId::Saves);
      break;
    }
    case MenuAction::QuickSave: {
      // FIXME don't allow quick saves before the in-game menu has been active once
      if (const auto* snapshot = m_shared.try_ctx<ctx::RendererSnapshot>()) {
        SaveGame("quick_save", m_shared, snapshot->surface);
      }
      m_dispatcher.enqueue<switch_menu_event>(MenuId::InGame);
      break;
    }
    case MenuAction::LoadGame: {
      m_dispatcher.enqueue<LoadGameEvent>(sys::GetSelectedSaveName(m_shared));
      break;
    }
    case MenuAction::DeleteGame: {
      const auto name = sys::GetSelectedSaveName(m_shared);
      sys::RemoveSaveEntry(m_shared, name);
      break;
    }
    case MenuAction::ChangeSavePreview: {
      sys::ChangeSavePreview(m_shared);
      break;
    }
    case MenuAction::DecrementSavesButtonGroupPage: {
      sys::DecrementSavesButtonGroupPage(m_shared);
      break;
    }
    case MenuAction::IncrementSavesButtonGroupPage: {
      sys::IncrementSavesButtonGroupPage(m_shared);
      break;
    }
    case MenuAction::ToggleFullscreen: {
      const auto enabled = sys::ToggleFullscreen(m_shared);
      m_dispatcher.enqueue<fullscreen_toggled_event>(enabled);
      break;
    }
    case MenuAction::ToggleIntegerScaling: {
      const auto enabled = sys::ToggleIntegerScaling(m_shared);
      m_dispatcher.enqueue<integer_scaling_toggled_event>(enabled);
      break;
    }
    case MenuAction::Quit: {
      m_dispatcher.enqueue<QuitEvent>();
      break;
    }
  }
}

void Game::on_switch_map(const SwitchMapEvent& event)
{
  auto& level = sys::CurrentLevel(m_shared);
  sys::StartLevelChangeAnimation(level.registry, event.map);
}

void Game::on_switch_menu(const switch_menu_event& event)
{
  sys::SwitchMenu(m_shared, m_dispatcher, event.id);
}

void Game::on_menu_switched(const menu_switched_event& event)
{
  const auto& menu = m_shared.get<comp::Menu>(event.entity);
  if (menu.id == MenuId::Saves) {
    sys::RefreshSavesMenu(m_shared);
  }
}

void Game::on_custom_animation_halfway(const CustomAnimationHalfwayEvent& event)
{
  switch (event.id) {
    case glob::sleep_id:
      sys::ChangeToNextDay(m_shared, m_dispatcher, glob::morning_hour);
      break;

    case glob::load_game_id:
      m_dispatcher.enqueue<switch_menu_event>(MenuId::InGame);
      break;

    case glob::switch_level_id:
      const auto next = sys::PrepareCurrentLevelBeforeSwitch(m_shared, event);
      sys::EnableLevel(m_shared, next);

      auto& level = sys::CurrentLevel(m_shared);
      sys::StartReverseOnlyBondAnimation(level.registry);

      break;
  }
}

void Game::on_show_inventory(const ShowInventoryEvent& event)
{
  auto& level = sys::CurrentLevel(m_shared);
  level.registry.emplace<comp::ActiveInventory>(event.inventory_entity);
}

void Game::on_close_inventory(const CloseInventoryEvent&)
{
  sys::CurrentLevel(m_shared).registry.clear<comp::ActiveInventory>();
}

void Game::on_sleep(const SleepEvent&)
{
  auto& level = sys::CurrentLevel(m_shared);
  sys::StartBondAnimation(level.registry, glob::sleep_id);
}

void Game::on_day_changed(const DayChangedEvent&)
{
  // TODO update the state of plants, etc.
}

void Game::on_spawn_particles(const SpawnParticlesEvent& event)
{
  auto& level = sys::CurrentLevel(m_shared);
  sys::SpawnParticles(level.registry,
                      event.position,
                      event.count,
                      event.duration,
                      event.color);
}

void Game::on_quit(const QuitEvent&)
{
  if (const auto* snapshot = m_shared.try_ctx<ctx::RendererSnapshot>()) {
    create_exit_save(m_shared, snapshot->surface);
  }

  m_quit = true;
}

}  // namespace wanderer
