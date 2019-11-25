#pragma once
#include "menu_state_machine.h"
#include "wanderer_core.h"
#include "font_bundle.h"
#include <map>

namespace albinjohansson::wanderer {

/**
 * The MenuStateMachineImpl class is an implementation of the IMenuStateMachine interface.
 *
 * @see IMenuStateMachine
 * @since 0.1.0
 */
class MenuStateMachineImpl final : public IMenuStateMachine {
 private:
  mutable FontBundle typewriterFonts;
  std::map<MenuID, IMenu_uptr> menus;
  MenuID activeMenuID = MenuID::HOME;

  void Put(MenuID id, IMenu_uptr menu);

 public:
  explicit MenuStateMachineImpl(IWandererCore* core);

  ~MenuStateMachineImpl() override;

  static IMenuStateMachine_uptr Create(IWandererCore* core);

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

  void HandleInput(const Input& input) noexcept override;

  void SetMenu(MenuID id) noexcept override;

  const IMenu& GetMenu() const override;
};

}
