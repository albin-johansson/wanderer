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

#include <centurion.hpp>        // ipoint
#include <rune/everything.hpp>  // basic_game, input, delta_time

#include "components/lvl/level.hpp"
#include "core/graphics/graphics_context.hpp"
#include "events/custom_animation_halfway_event.hpp"
#include "events/day_changed_event.hpp"
#include "events/inventory_events.hpp"
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
class Game final : public rune::basic_game<graphics_context>
{
 public:
  explicit Game(graphics_type& graphics);

  ~Game();

  void on_start() override;

  void on_exit() override;

  void handle_input(const rune::input& input) override;

  void tick(float dt) override;

  void render(graphics_type& gfx) const override;

  void load_save(const std::string& name, graphics_type& graphics);

  template <typename Event>
  [[nodiscard]] auto sink()
  {
    return m_dispatcher.sink<Event>();
  }

  [[nodiscard]] auto should_quit() const noexcept -> bool override
  {
    return m_quit;
  }

 private:
  mutable entt::registry m_shared;  // Contains menus, settings, etc.
  entt::dispatcher m_dispatcher;
  cen::ipoint m_mousePos;
  mutable bool m_updateSnapshot{};
  bool m_quit{};

  [[nodiscard]] auto is_paused() const -> bool;

  void on_button_pressed(const button_pressed_event& event);

  void on_switch_map(const switch_map_event& event);

  void on_switch_menu(const switch_menu_event& event);

  void on_menu_switched(const menu_switched_event& event);

  void on_custom_animation_halfway(const custom_animation_halfway_event& event);

  void on_show_inventory(const show_inventory_event& event);

  void on_close_inventory(const close_inventory_event&);

  void on_sleep(const sleep_event&);

  void on_day_changed(const day_changed_event& event);

  void on_spawn_particles(const spawn_particles_event& event);

  void on_quit(const quit_event&);
};

}  // namespace wanderer
