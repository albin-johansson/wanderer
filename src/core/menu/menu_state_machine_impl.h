#pragma once
#include <map>
#include <memory>
#include "menu_state_machine.h"
#include "font_bundle.h"

namespace albinjohansson::wanderer {

class IWandererCore;

/**
 * The MenuStateMachineImpl class is an implementation of the IMenuStateMachine interface.
 *
 * @see IMenuStateMachine
 * @since 0.1.0
 */
class MenuStateMachineImpl final : public IMenuStateMachine {
 private:
  mutable FontBundle typewriterFonts;
  std::map<MenuID, std::unique_ptr<IMenu>> menus;
  MenuID activeMenuID = MenuID::Home;

  void put(MenuID id, std::unique_ptr<IMenu> menu);

 public:
  explicit MenuStateMachineImpl(IWandererCore* core);

  ~MenuStateMachineImpl() override;

  void draw(centurion::Renderer& renderer, const Viewport& viewport) const override;

  void handle_input(const Input& input) noexcept override;

  void set_menu(MenuID id) noexcept override;

  [[nodiscard]]
  const IMenu& get_menu() const override;
};

}
