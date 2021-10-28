#pragma once

/// \defgroup systems Systems
/// \brief Contains all of the systems, that provide all of the game logic.

/// \defgroup components Components
/// \brief Contains all of the components.

/// \defgroup ctx Context components
/// \brief Contains all singleton components.

/// \defgroup core Core
/// \brief Contains "core" game components, used throughout the game.

/// \defgroup events Events
/// \brief Contains all events emitted in the game.

#include <centurion.hpp>  // ipoint
#include <rune/rune.hpp>  // engine

#include "core/graphics/graphics_context.hpp"
#include "events/custom_animation_halfway_event.hpp"
#include "events/day_changed_event.hpp"
#include "events/inventory_events.hpp"
#include "events/load_game_event.hpp"
#include "events/menu_events.hpp"
#include "events/quit_event.hpp"
#include "events/sleep_event.hpp"
#include "events/spawn_particles_event.hpp"
#include "events/switch_map_event.hpp"

namespace wanderer {

/**
 * \brief Represents the Wanderer game.
 *
 * \details This class is responsible for managing the game state and updating the
 * systems. This class is the core of the entire game.
 *
 * \ingroup core
 */
class Game final
{
 public:
  Game();

  auto Run() -> int;

 private:
  rune::engine mEngine;
  GraphicsContext mGraphics;
  cen::ipoint mMousePos;  // TODO remove
  mutable bool mUpdateSnapshot{};
  bool mQuit{};

  void OnStart();

  void OnExit();

  void HandleInput();

  void Tick(entt::registry& shared, entt::dispatcher& dispatcher, float dt);

  void Render(entt::registry& shared);

  [[nodiscard]] auto IsPaused() const -> bool;

  void OnFullscreenToggled(const fullscreen_toggled_event& event);

  void OnIntegerScalingToggled(const integer_scaling_toggled_event& event);

  void OnLoadGameEvent(const LoadGameEvent& event);

  void OnButtonPressed(const button_pressed_event& event);

  void OnSwitchMap(const SwitchMapEvent& event);

  void OnSwitchMenu(const switch_menu_event& event);

  void OnMenuSwitched(const menu_switched_event& event);

  void OnCustomAnimationHalfway(const CustomAnimationHalfwayEvent& event);

  void OnShowInventory(const ShowInventoryEvent& event);

  void OnCloseInventory(const CloseInventoryEvent&);

  void OnSleep(const SleepEvent&);

  void OnDayChanged(const DayChangedEvent& event);

  void OnSpawnParticles(const SpawnParticlesEvent& event);

  void OnQuit(const QuitEvent&);
};

}  // namespace wanderer
