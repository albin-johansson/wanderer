#pragma once
#include "menu_state_machine.h"
#include "font_bundle.h"
#include <map>
#include <memory>

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
  MenuID activeMenuID = MenuID::HOME;

  void Put(MenuID id, std::unique_ptr<IMenu> menu);

 public:
  explicit MenuStateMachineImpl(IWandererCore* core);

  ~MenuStateMachineImpl() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void HandleInput(const Input& input) noexcept override;

  void SetMenu(MenuID id) noexcept override;

  [[nodiscard]]
  const IMenu& GetMenu() const override;
};

}
