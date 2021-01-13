#pragma once

#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>

#include "close_inventory_event.hpp"
#include "cursor_manager.hpp"
#include "delta.hpp"
#include "graphics_context.hpp"
#include "level.hpp"
#include "level_fade_events.hpp"
#include "level_manager.hpp"
#include "menu_manager.hpp"
#include "show_inventory_event.hpp"
#include "switch_map_event.hpp"

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
   * \param mouseState the current mouse input state.
   * \param keyState the current keyboard input state.
   */
  void handle_input(const cen::mouse_state& mouseState,
                    const cen::key_state& keyState);

  /**
   * \brief Updates the state of the game.
   *
   * \param dt the delta_t time, in seconds.
   */
  void tick(delta_t dt);

  /**
   * \brief Renders the game.
   *
   * \param renderer the renderer used to render the game.
   */
  void render(cen::renderer& renderer, const cen::ipoint& mousePos);

  /**
   * \brief Indicates whether or not the game should quit.
   *
   * \return `true` if the game should quit; `false` otherwise.
   */
  [[nodiscard]] auto quit_requested() const noexcept -> bool
  {
    return m_menus.quit_requested();
  }

 private:
  entt::dispatcher m_dispatcher;
  level_manager m_levels;
  menu_manager m_menus;
  cursor_manager m_cursors;

  [[nodiscard]] auto fully_paused() const -> bool;

  [[nodiscard]] auto weakly_paused() const -> bool;

  void on_switch_map(const comp::switch_map_event& event);

  void on_level_animation_faded_in(const comp::level_faded_in_event& event);

  void on_level_animation_faded_out(comp::level_faded_out_event);

  void on_show_inventory(const comp::show_inventory_event& event);

  void on_close_inventory(comp::close_inventory_event);
};

}  // namespace wanderer
