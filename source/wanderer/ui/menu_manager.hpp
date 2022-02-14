#pragma once

#include <unordered_map>  // unordered_map

#include <entt/entt.hpp>

#include "menu.hpp"
#include "menu_id.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer {

/**
 * \brief A simple facade for the different menus.
 */
class menu_manager final
{
 public:
  /**
   * \brief Initializes all menus.
   *
   * \param cfg the configuration that will be used.
   */
  explicit menu_manager(const game_cfg& cfg);

  /**
   * \brief Changes the active menu.
   *
   * \param menu the new active menu.
   */
  void switch_to(menu_id menu);

  /**
   * \brief Polls the currently active menu.
   *
   * \param input the current input state.
   * \param dispatcher the event dispatcher that will be used.
   */
  void poll(const input_state& input, entt::dispatcher& dispatcher);

  /**
   * \brief Renders the currently active menu.
   *
   * \param graphics the graphics context that will be used.
   */
  void render(graphics_ctx& graphics);

  /**
   * \brief Indicates whether the current menu is blocking.
   *
   * \return `true` if the current menu is blocking; `false` otherwise.
   */
  [[nodiscard]] auto is_blocking() const -> bool;

 private:
  std::unordered_map<menu_id, ui_menu> mMenus;
  menu_id mCurrentMenu{menu_id::home};
};

}  // namespace wanderer
