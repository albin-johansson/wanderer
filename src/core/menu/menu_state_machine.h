#pragma once
#include "menu.h"
#include "menu_id.h"
#include <memory>

namespace wanderer::core {

/**
 * The IMenuStateMachine interface is a subinterface of IMenu that specifies objects that
 * represent a state machine that can switch between different menu states by itself.
 *
 * @see IMenu
 * @since 0.1.0
 */
class IMenuStateMachine : public IMenu {
 protected:
  IMenuStateMachine() = default;

 public:
  ~IMenuStateMachine() override = default;

  /**
   * Sets the active menu.
   *
   * @param id the identifier associated with the desired menu.
   * @since 0.1.0
   */
  virtual void SetMenu(MenuID id) = 0;
};

using IMenuStateMachine_uptr = std::unique_ptr<IMenuStateMachine>;
using IMenuStateMachine_sptr = std::shared_ptr<IMenuStateMachine>;
using IMenuStateMachine_wptr = std::weak_ptr<IMenuStateMachine>;

}
