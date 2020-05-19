#pragma once
#include <map>
#include <memory>

#include "font_bundle.h"
#include "menu_state_machine.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class IWandererCore;

/**
 * The MenuStateMachineImpl class is an implementation of the IMenuStateMachine
 * interface.
 *
 * @see IMenuStateMachine
 * @since 0.1.0
 */
class MenuStateMachineImpl final : public IMenuStateMachine {
 public:
  explicit MenuStateMachineImpl();

  ~MenuStateMachineImpl() override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

  void handle_input(const Input& input) noexcept override;

  void add_menu(MenuID id, UniquePtr<IMenu> menu) override;

  void set_menu(MenuID id) noexcept override;

  [[nodiscard]] const IMenu& get_menu() const override;

 private:
  mutable FontBundle m_typewriterFonts;
  std::map<MenuID, UniquePtr<IMenu>> m_menus;
  MenuID m_activeMenuID = MenuID::Home;
};

}  // namespace albinjohansson::wanderer
