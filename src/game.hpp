#pragma once

#include <centurion.hpp>

#include "button_pressed_event.hpp"
#include "changed_setting_event.hpp"
#include "close_inventory_event.hpp"
#include "delta.hpp"
#include "graphics_context.hpp"
#include "level.hpp"
#include "level_fade_events.hpp"
#include "level_manager.hpp"
#include "particle_event.hpp"
#include "quit_event.hpp"
#include "show_inventory_event.hpp"
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
   * \param mouse the current mouse input state.
   * \param keyboard the current keyboard input state.
   */
  void handle_input(const cen::mouse& mouse, const cen::keyboard& keyboard);

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

  void on_switch_map(const comp::switch_map_event& event);

  void on_switch_menu_event(const comp::switch_menu_event& event);

  void on_button_pressed(const comp::button_pressed_event& event);

  void on_changed_setting(const comp::changed_setting_event& event);

  void on_level_animation_faded_in(const comp::level_faded_in_event& event);

  void on_level_animation_faded_out(comp::level_faded_out_event);

  void on_show_inventory(const comp::show_inventory_event& event);

  void on_close_inventory(comp::close_inventory_event);

  void on_particle_event(const comp::particle_event& event);

  void on_quit_event(comp::quit_event);
};

}  // namespace wanderer
