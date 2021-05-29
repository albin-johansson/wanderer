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
#include <rune.hpp>       // input, delta_time

#include "components/map/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/bond_animation_halfway_event.hpp"
#include "events/button_pressed_event.hpp"
#include "events/close_inventory_event.hpp"
#include "events/day_changed_event.hpp"
#include "events/quit_event.hpp"
#include "events/show_inventory_event.hpp"
#include "events/sleep_event.hpp"
#include "events/spawn_particles_event.hpp"
#include "events/switch_map_event.hpp"
#include "events/switch_menu_event.hpp"

namespace wanderer {

/**
 * \class game
 *
 * \ingroup core
 *
 * \brief Represents the Wanderer game.
 *
 * \details This class is responsible for managing the game state and
 * updating the systems. This class is the core of the entire game.
 *
 * \headerfile game.hpp
 */
class game final
{
 public:
  explicit game(graphics_context& graphics);

  ~game();

  void on_start();

  void on_exit();

  void handle_input(const rune::input& input);

  void tick(rune::delta_time dt);

  void render(graphics_context& graphics);

  void load_save(const std::string& name, graphics_context& graphics);

  template <typename Event>
  [[nodiscard]] auto sink()
  {
    return m_dispatcher.sink<Event>();
  }

  [[nodiscard]] auto should_quit() const noexcept -> bool
  {
    return m_quit;
  }

 private:
  entt::registry m_shared;  // Shared data registry, contains menus, settings, etc.
  entt::dispatcher m_dispatcher;
  cen::ipoint m_mousePos;
  bool m_updateSnapshot{};
  bool m_quit{};

  [[nodiscard]] auto is_paused() const -> bool;

  void on_button_pressed(const button_pressed_event& event);

  void on_switch_map(const switch_map_event& event);

  void on_switch_menu(const switch_menu_event& event);

  void on_bond_animation_halfway(const bond_animation_halfway_event& event);

  void on_show_inventory(const show_inventory_event& event);

  void on_close_inventory(const close_inventory_event&);

  void on_sleep(const sleep_event&);

  void on_day_changed(const day_changed_event& event);

  void on_spawn_particles(const spawn_particles_event& event);

  void on_quit(const quit_event&);
};

}  // namespace wanderer
