#pragma once

#include <centurion.hpp>

#include "button_pressed_event.hpp"
#include "close_inventory_event.hpp"
#include "delta.hpp"
#include "graphics_context.hpp"
#include "input.hpp"
#include "level.hpp"
#include "level_fade_events_event.hpp"
#include "level_manager.hpp"
#include "quit_event.hpp"
#include "show_inventory_event.hpp"
#include "spawn_particles_event.hpp"
#include "switch_map_event.hpp"
#include "switch_menu_event.hpp"

namespace wanderer {

/**
 * \class game
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

  ~game() noexcept;

  /**
   * \brief Responds to user input.
   *
   * \param input the current input state.
   */
  void handle_input(const input& input);

  /**
   * \brief Updates the state of the game.
   *
   * \param dt the delta_t time, in seconds.
   */
  void tick(delta_t dt);

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
  entt::registry m_menus;  // Menu registry, also contains settings
  bool m_quit{false};

  [[nodiscard]] auto is_paused() const -> bool;

  [[nodiscard]] auto is_inventory_active() const -> bool;

  void on_switch_map(const event::switch_map& event);

  void on_switch_menu_event(const event::switch_menu& event);

  void on_button_pressed(const event::button_pressed& event);

  void on_level_animation_faded_in(const event::level_faded_in& event);

  void on_level_animation_faded_out(event::level_faded_out);

  void on_show_inventory(const event::show_inventory_event& event);

  void on_close_inventory(event::close_inventory);

  void on_particle_event(const event::spawn_particles& event);

  void on_quit_event(event::quit_event);
};

}  // namespace wanderer
