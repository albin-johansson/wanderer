#pragma once

#include <cassert>  // assert
#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>
#include <unordered_map>  // unordered_map

#include "maybe.hpp"
#include "menu.hpp"

namespace wanderer {

class menu_manager final
{
 public:
  menu_manager();

  void update(const cen::mouse_state& mouseState,
              const cen::key_state& keyState);

  void render(cen::renderer& renderer);

  void switch_to(menu_id menu);

  [[nodiscard]] auto is_blocking() const -> bool
  {
    return active_menu().is_blocking();
  }

  [[nodiscard]] auto quit_requested() const noexcept -> bool
  {
    return m_shouldQuit;
  }

 private:
  maybe<menu_id> m_current;
  std::unordered_map<menu_id, menu> m_menus;
  bool m_shouldQuit{};

  [[nodiscard]] auto active_menu() const -> const menu&
  {
    assert(m_current.has_value());
    return m_menus.at(*m_current);
  }

  [[nodiscard]] auto active_menu() -> menu&
  {
    assert(m_current.has_value());
    return m_menus.at(*m_current);
  }

  void perform_action(menu_action action);
};

}  // namespace wanderer
