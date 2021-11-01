#include "game.hpp"

#include "components/items/inventory.hpp"
#include "components/renderer_snapshot.hpp"
#include "components/settings.hpp"
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
#include "systems/level_system.hpp"
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

Game::Game()
    : mEngine{rune::configuration{.window_title = "Wanderer", .max_tick_rate = 240}}
    , mGraphics{mEngine.window()}
{
  mCenDispatcher.bind<cen::quit_event>().to<&Game::OnWindowClose>(this);
  mEngine.set_registry(sys::MakeSharedRegistry());
  mEngine.set_dispatcher(MakeDispatcher());
  mEngine.mouse().set_logical_size(glob::logical_size<>);

  mEngine.on_start<&Game::OnStart>(this);
  mEngine.on_exit<&Game::OnExit>(this);
  mEngine.add_input_system<&Game::HandleInput>(this);
  mEngine.add_logic_system<&Game::Tick>(this);
  mEngine.add_render_system<&Game::Render>(this);

  auto& d = mEngine.dispatcher();
  d.sink<FullscreenToggledEvent>().connect<&Game::OnFullscreenToggled>(this);
  d.sink<IntegerScalingToggledEvent>().connect<&Game::OnIntegerScalingToggled>(this);
  d.sink<LoadGameEvent>().connect<&Game::OnLoadGameEvent>(this);
  d.sink<SwitchMapEvent>().connect<&Game::OnSwitchMap>(this);
  d.sink<SwitchMenuEvent>().connect<&Game::OnSwitchMenu>(this);
  d.sink<MenuSwitchedEvent>().connect<&Game::OnMenuSwitched>(this);
  d.sink<ButtonPressedEvent>().connect<&Game::OnButtonPressed>(this);
  d.sink<ShowInventoryEvent>().connect<&Game::OnShowInventory>(this);
  d.sink<CloseInventoryEvent>().connect<&Game::OnCloseInventory>(this);
  d.sink<SleepEvent>().connect<&Game::OnSleep>(this);
  d.sink<DayChangedEvent>().connect<&Game::OnDayChanged>(this);
  d.sink<CustomAnimationHalfwayEvent>().connect<&Game::OnCustomAnimationHalfway>(this);
  d.sink<SpawnParticlesEvent>().connect<&Game::OnSpawnParticles>(this);
  d.sink<QuitEvent>().connect<&Game::OnQuit>(this);

  LoadLevels(mEngine.registry(), mGraphics);
}

auto Game::Run() -> int
{
  return mEngine.run();
}

void Game::OnStart()
{
  auto& shared = mEngine.registry();
  auto& dispatcher = mEngine.dispatcher();

  sys::LoadSettings(shared);
  shared.set<ctx::Binds>(sys::LoadBinds());
  shared.ctx<ctx::TimeOfDay>().seconds = sys::HourToSeconds(12);

  {
    auto& data = shared.emplace<comp::FpsData>(shared.create());
    data.then = cen::counter::ticks();
    data.interval = ms_t{500};
    data.next_update = data.then + data.interval;
  }

  const auto& settings = shared.ctx<ctx::Settings>();
  dispatcher.enqueue<FullscreenToggledEvent>(settings.fullscreen);
  dispatcher.enqueue<IntegerScalingToggledEvent>(settings.integer_scaling);

  sys::SyncSettingsMenu(shared);
  dispatcher.update();
}

void Game::OnExit()
{
  auto& shared = mEngine.registry();
  sys::SaveSettingsBeforeExit(shared);
}

void Game::HandleInput()
{
  auto& shared = mEngine.registry();
  auto& dispatcher = mEngine.dispatcher();

  const auto& keyboard = mEngine.keyboard();
  const auto& mouse = mEngine.mouse();

  mMousePos = mouse.position();
  sys::UpdateMenu(shared, dispatcher, keyboard, mouse);

  auto& level = sys::CurrentLevel(shared);
  sys::UpdateInput(level.registry, dispatcher, keyboard, shared.ctx<ctx::Binds>());
}

void Game::Tick(entt::registry& shared, entt::dispatcher& dispatcher, const float dt)
{
  if (mQuit) {
    mEngine.stop();
    return;
  }

  auto& level = sys::CurrentLevel(shared);
  sys::UpdateFps(shared, dt);

  sys::UpdateRenderBounds(level.registry);
  sys::UpdateCustomAnimations(level.registry, dispatcher, dt);

  if (IsPaused()) {
    return;
  }

  sys::UpdateTime(shared, dispatcher, dt);
  sys::UpdateHumanoidStates(level.registry, dispatcher);

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

void Game::Render(entt::registry& shared)
{
  if (mQuit) {
    return;
  }

  shared.set<ref<GraphicsContext>>(mGraphics);

  auto& level = sys::CurrentLevel(shared);
  level.registry.set<ref<GraphicsContext>>(mGraphics);

  auto& renderer = mGraphics.GetRenderer();
  renderer.clear_with(cen::colors::black);

  sys::TranslateViewport(level.registry);

  sys::RenderTileLayers(level.registry);
  sys::RenderDrawables(level.registry);
  sys::RenderParticles(level.registry);

  if (sys::IsCurrentLevelOutside(shared)) {
    sys::RenderLights(level.registry, shared.ctx<ctx::TimeOfDay>());
  }

  sys::RenderClock(shared);

  if (mUpdateSnapshot) {
    shared.set<ctx::RendererSnapshot>(renderer.capture(mGraphics.GetFormat()));
    mUpdateSnapshot = false;
  }

  if constexpr (cen::is_debug_build()) {
    sys::RenderDebugInfo(level.registry);
  }

  sys::RenderHud(shared, mMousePos);

  sys::RenderActiveMenu(shared);
  sys::RenderCustomAnimations(level.registry);

  sys::RenderFps(shared);

  if constexpr (cen::is_debug_build()) {
    sys::RenderMenuDebugInfo(shared);
  }

  renderer.present();

  /* Let's embrace our paranoia and unset the renderer context variables! */
  level.registry.unset<ref<GraphicsContext>>();
  shared.unset<ref<GraphicsContext>>();
}

auto Game::IsPaused() const -> bool
{
  return sys::IsCurrentMenuBlocking(mEngine.registry());
}

void Game::OnFullscreenToggled(const FullscreenToggledEvent& event)
{
  auto& window = mEngine.window();

  // TODO make it possible to specify whether to use real fullscreen or fullscreen desktop
  if (event.enabled) {
    window.set_size(cen::screen::size().value());
    window.set_fullscreen_desktop(true);
  }
  else {
    window.set_fullscreen_desktop(false);
    window.set_width(cen::screen::width().value() / 2);
    window.set_height(cen::screen::height().value() / 2);
  }
}

void Game::OnIntegerScalingToggled(const IntegerScalingToggledEvent& event)
{
  mGraphics.GetRenderer().set_logical_integer_scaling(event.enabled);
}

void Game::OnLoadGameEvent(const LoadGameEvent& event)
{
  auto& shared = mEngine.registry();
  LoadGame(shared, mGraphics, event.name);

  auto& level = sys::CurrentLevel(shared);
  sys::StartBondAnimation(level.registry, glob::load_game_id);
}

void Game::OnButtonPressed(const ButtonPressedEvent& event)
{
  auto& shared = mEngine.registry();
  auto& dispatcher = mEngine.dispatcher();
  switch (event.action) {
    default:
      [[fallthrough]];
    case MenuAction::None:
      break;

    case MenuAction::GotoInGame: {
      dispatcher.enqueue<SwitchMenuEvent>(MenuId::InGame);
      break;
    }
    case MenuAction::GotoHome: {
      mUpdateSnapshot = true;
      dispatcher.enqueue<SwitchMenuEvent>(MenuId::Home);
      break;
    }
    case MenuAction::GotoControls: {
      dispatcher.enqueue<SwitchMenuEvent>(MenuId::Controls);
      break;
    }
    case MenuAction::GotoSettings: {
      dispatcher.enqueue<SwitchMenuEvent>(MenuId::Settings);
      break;
    }
    case MenuAction::GotoSaves: {
      dispatcher.enqueue<SwitchMenuEvent>(MenuId::Saves);
      break;
    }
    case MenuAction::QuickSave: {
      // FIXME don't allow quick saves before the in-game menu has been active once
      if (const auto* snapshot = shared.try_ctx<ctx::RendererSnapshot>()) {
        SaveGame("quick_save", shared, snapshot->surface);
      }
      dispatcher.enqueue<SwitchMenuEvent>(MenuId::InGame);
      break;
    }
    case MenuAction::LoadGame: {
      dispatcher.enqueue<LoadGameEvent>(sys::GetSelectedSaveName(shared));
      break;
    }
    case MenuAction::DeleteGame: {
      const auto name = sys::GetSelectedSaveName(shared);
      sys::RemoveSaveEntry(shared, name);
      break;
    }
    case MenuAction::ChangeSavePreview: {
      sys::ChangeSavePreview(shared);
      break;
    }
    case MenuAction::DecrementSavesButtonGroupPage: {
      sys::DecrementSavesButtonGroupPage(shared);
      break;
    }
    case MenuAction::IncrementSavesButtonGroupPage: {
      sys::IncrementSavesButtonGroupPage(shared);
      break;
    }
    case MenuAction::ToggleFullscreen: {
      const auto enabled = sys::ToggleFullscreen(shared);
      dispatcher.enqueue<FullscreenToggledEvent>(enabled);
      break;
    }
    case MenuAction::ToggleIntegerScaling: {
      const auto enabled = sys::ToggleIntegerScaling(shared);
      dispatcher.enqueue<IntegerScalingToggledEvent>(enabled);
      break;
    }
    case MenuAction::Quit: {
      dispatcher.enqueue<QuitEvent>();
      break;
    }
  }
}

void Game::OnSwitchMap(const SwitchMapEvent& event)
{
  auto& level = sys::CurrentLevel(mEngine.registry());
  sys::StartLevelChangeAnimation(level.registry, event.map);
}

void Game::OnSwitchMenu(const SwitchMenuEvent& event)
{
  sys::SwitchMenu(mEngine.registry(), mEngine.dispatcher(), event.id);
}

void Game::OnMenuSwitched(const MenuSwitchedEvent& event)
{
  auto& shared = mEngine.registry();
  const auto& menu = shared.get<comp::Menu>(event.entity);
  if (menu.id == MenuId::Saves) {
    sys::RefreshSavesMenu(shared);
  }
}

void Game::OnCustomAnimationHalfway(const CustomAnimationHalfwayEvent& event)
{
  auto& shared = mEngine.registry();
  auto& dispatcher = mEngine.dispatcher();
  switch (event.id) {
    case glob::sleep_id:
      sys::ChangeToNextDay(shared, dispatcher, glob::morning_hour);
      break;

    case glob::load_game_id:
      dispatcher.enqueue<SwitchMenuEvent>(MenuId::InGame);
      break;

    case glob::switch_level_id:
      const auto next = sys::PrepareCurrentLevelBeforeSwitch(shared, event);
      sys::EnableLevel(shared, next);

      auto& level = sys::CurrentLevel(shared);
      sys::StartReverseOnlyBondAnimation(level.registry);

      break;
  }
}

void Game::OnShowInventory(const ShowInventoryEvent& event)
{
  auto& shared = mEngine.registry();
  auto& level = sys::CurrentLevel(shared);
  level.registry.emplace<comp::ActiveInventory>(event.inventory_entity);
}

void Game::OnCloseInventory(const CloseInventoryEvent&)
{
  auto& shared = mEngine.registry();
  sys::CurrentLevel(shared).registry.clear<comp::ActiveInventory>();
}

void Game::OnSleep(const SleepEvent&)
{
  auto& shared = mEngine.registry();
  auto& level = sys::CurrentLevel(shared);
  sys::StartBondAnimation(level.registry, glob::sleep_id);
}

void Game::OnDayChanged([[maybe_unused]] const DayChangedEvent& event)
{
  // TODO update the state of plants, etc.
}

void Game::OnSpawnParticles(const SpawnParticlesEvent& event)
{
  auto& shared = mEngine.registry();
  auto& level = sys::CurrentLevel(shared);
  sys::SpawnParticles(level.registry,
                      event.position,
                      event.count,
                      event.duration,
                      event.color);
}

void Game::OnQuit()
{
  auto& shared = mEngine.registry();
  if (const auto* snapshot = shared.try_ctx<ctx::RendererSnapshot>()) {
    create_exit_save(shared, snapshot->surface);
  }

  mQuit = true;
}

void Game::OnWindowClose(const cen::quit_event&)
{
  OnQuit();
}

}  // namespace wanderer
