#pragma once

#include <cen/key_state.hpp>
#include <cen/mouse_state.hpp>
#include <cen/renderer.hpp>
#include <cen/texture.hpp>
#include <filesystem>  // path
#include <optional>    // optional
#include <string>      // string
#include <vector>      // vector

#include "key_bind.hpp"
#include "menu_action.hpp"
#include "menu_button.hpp"
#include "menu_id.hpp"

namespace wanderer {

class menu final
{
  friend auto make_menu(const std::filesystem::path& path) -> menu;

 public:
  /**
   * \brief Queries the buttons and returns the action that should be executed,
   * if any.
   *
   * \param mouseState the current mouse state.
   *
   * \return the action that should be executed; `std::nullopt` if there is
   * none.
   */
  [[nodiscard]] auto query_buttons(const cen::mouse_state& mouseState)
      -> std::optional<menu_action>;

  /**
   * \brief Queries the binds and returns the action that should be executed,
   * if any.
   *
   * \param keyState the current key state.
   *
   * \return the action that should be executed; `std::nullopt` if there is
   * none.
   */
  [[nodiscard]] auto query_binds(const cen::key_state& keyState)
      -> std::optional<menu_action>;

  /**
   * \brief Renders the menu.
   *
   * \param renderer the renderer that will be used.
   */
  void render(cen::renderer& renderer) const;

  /**
   * \brief Indicates whether or not the menu is blocking.
   *
   * \details A menu is blocking if it is meant to block the game from
   * updating, such as a main menu, for example.
   *
   * \return `true` if the menu is blocking; `false` otherwise
   */
  [[nodiscard]] auto is_blocking() const noexcept -> bool
  {
    return m_blocking;
  }

 private:
  std::string m_title;
  std::vector<menu_button> m_buttons;
  std::vector<key_bind> m_binds;
  mutable std::optional<cen::texture> m_titleTexture;
  mutable std::optional<cen::ipoint> m_titlePos;
  bool m_blocking{};

  void load_title_texture(cen::renderer& renderer) const;

  void render_title(cen::renderer& renderer) const;
};

}  // namespace wanderer
