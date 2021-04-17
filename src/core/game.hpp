#pragma once

/// \defgroup systems Systems
/// \brief Contains all of the systems, that provide all of the game logic.

/// \defgroup components Components
/// \brief Contains all of the components.

/// \defgroup core Core
/// \brief Contains "core" game components, used throughout the game.

/// \defgroup events Events
/// \brief Contains all events emitted in the game.

#include <centurion.hpp>

#include "core/aliases/delta_time.hpp"
#include "core/graphics/graphics_context.hpp"
#include "core/input.hpp"
#include "core/levels/level.hpp"
#include "core/levels/level_manager.hpp"
#include "events/button_pressed_event.hpp"
#include "events/close_inventory_event.hpp"
#include "events/level_fade_events_event.hpp"
#include "events/quit_event.hpp"
#include "events/show_inventory_event.hpp"
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
  /**
   * \brief Creates a `game` instance.
   *
   * \param graphics the associated graphics context.
   */
  explicit game(graphics_context& graphics);

  ~game();

  /**
   * \brief Responds to user input.
   *
   * \param input the current input state.
   */
  void handle_input(const input& input);

  /**
   * \brief Updates the state of the game.
   *
   * \param dt the delta time, in seconds.
   */
  void tick(delta_time dt);

  /**
   * \brief Renders the game.
   *
   * \param graphics the graphics context used to render the game.
   * \param mousePos the current position of the mouse.
   */
  void render(graphics_context& graphics, cen::ipoint mousePos);

  void on_start();

  void on_exit();

  template <typename Event>
  [[nodiscard]] decltype(auto) sink()
  {
    return m_dispatcher.sink<Event>();
  }

  /**
   * \brief Indicates whether or not the game should quit.
   *
   * \return `true` if the game should quit; `false` otherwise.
   */
  [[nodiscard]] auto quit_requested() const noexcept -> bool
  {
    return m_quit;
  }

 private:
  entt::dispatcher m_dispatcher;
  level_manager m_levels;
  entt::registry m_shared;  // Shared data registry, contains menus, settings, etc.
  bool m_quit{false};

  [[nodiscard]] auto is_paused() const -> bool;

  [[nodiscard]] auto is_inventory_active() const -> bool;

  void on_switch_map(const switch_map_event& event);

  void on_switch_menu_event(const switch_menu_event& event);

  void on_button_pressed(const button_pressed_event& event);

  void on_level_animation_faded_in(const level_faded_in_event& event);

  void on_level_animation_faded_out(const level_faded_out_event&);

  void on_show_inventory(const show_inventory_event& event);

  void on_close_inventory(const close_inventory_event&);

  void on_particle_event(const spawn_particles_event& event);

  void on_quit_event(const quit_event&);
};

}  // namespace wanderer
