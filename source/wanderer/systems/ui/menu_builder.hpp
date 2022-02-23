#pragma once

#include <functional>  // reference_wrapper
#include <string>      // string

#include <centurion.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "wanderer/core/graphics.hpp"
#include "wanderer/data/components/ui.hpp"

namespace wanderer::sys::ui {

/**
 * \brief Builder used to create UI menus.
 */
class menu_builder final
{
 public:
  /**
   * \brief Starts building a new menu.
   *
   * \param registry the registry that will host the menu.
   *
   * \return the builder.
   */
  [[nodiscard]] static auto build(entt::registry& registry) -> menu_builder;

  /**
   * \brief Makes the menu blocking.
   *
   * \return the builder.
   */
  auto blocking() -> menu_builder&;

  /**
   * \brief Sets the menu title label.
   *
   * \param title the title text.
   *
   * \return the builder.
   */
  auto title(std::string title) -> menu_builder&;

  /**
   * \brief Adds a small label to the menu.
   *
   * \param text the label text.
   * \param offset the anchor offset.
   * \param ha the horizontal anchor.
   * \param va the vertical anchor.
   *
   * \return the builder
   */
  auto s_label(std::string text, const glm::vec2& offset, h_anchor ha, v_anchor va)
      -> menu_builder&;

  /**
   * \brief Adds a medium label to the menu.
   *
   * \param text the label text.
   * \param offset the anchor offset.
   * \param ha the horizontal anchor.
   * \param va the vertical anchor.
   *
   * \return the builder
   */
  auto m_label(std::string text, const glm::vec2& offset, h_anchor ha, v_anchor va)
      -> menu_builder&;

  /**
   * \brief Adds a large label to the menu.
   *
   * \param text the label text.
   * \param offset the anchor offset.
   * \param ha the horizontal anchor.
   * \param va the vertical anchor.
   *
   * \return the builder
   */
  auto l_label(std::string text, const glm::vec2& offset, h_anchor ha, v_anchor va)
      -> menu_builder&;

  /**
   * \brief Adds a huge label to the menu.
   *
   * \param text the label text.
   * \param offset the anchor offset.
   * \param ha the horizontal anchor.
   * \param va the vertical anchor.
   *
   * \return the builder
   */
  auto h_label(std::string text, const glm::vec2& offset, h_anchor ha, v_anchor va)
      -> menu_builder&;

  /**
   * \brief Adds a button to the menu.
   *
   * \param label the label text.
   * \param action the associated action when triggered.
   * \param offset the anchor offset.
   *
   * \return the builder.
   */
  auto button(std::string label, action_id action, const glm::vec2& offset)
      -> menu_builder&;

  /**
   * \brief Adds a button with an indicator of a boolean setting value.
   *
   * \param label the button label.
   * \param action the action emitted when the button is pressed.
   * \param flag the settings flag to observe.
   * \param offset the button offset.
   *
   * \return the builder.
   */
  auto toggle(std::string label,
              action_id action,
              uint64 flag,
              const glm::vec2& offset,
              h_anchor ha,
              v_anchor va) -> menu_builder&;

  /**
   * \brief Adds a key bind to the menu.
   *
   * \param key the key that triggers the action.
   * \param action the action identifier that will be emitted.
   *
   * \return the builder.
   */
  auto bind(const cen::scan_code& key, action_id action) -> menu_builder&;

  /**
   * \brief Returns the created menu entity.
   *
   * \return a menu entity.
   */
  [[nodiscard]] auto result() const noexcept -> entt::entity { return mEntity; }

 private:
  std::reference_wrapper<entt::registry> mRegistry;
  entt::entity mEntity{entt::null};

  explicit menu_builder(entt::registry& registry);

  [[nodiscard]] auto get_menu() -> comp::ui_menu&;

  void add_label(entt::entity entity,
                 std::string text,
                 font_size size,
                 const glm::vec2& offset,
                 h_anchor ha,
                 v_anchor va);

  void add_label(std::string text,
                 font_size size,
                 const glm::vec2& offset,
                 h_anchor ha,
                 v_anchor va);
};

}  // namespace wanderer::sys::ui
