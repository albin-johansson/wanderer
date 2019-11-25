#pragma once
#include "menu.h"
#include "menu_id.h"
#include <memory>

namespace albinjohansson::wanderer {

class IMenuStateMachine {
 protected:
  IMenuStateMachine() = default;

 public:
  virtual ~IMenuStateMachine() = default;

  virtual void HandleInput(const Input& input) = 0;

  virtual void Draw(Renderer& renderer, const Viewport& viewport) const = 0;

  /**
   * Sets the active menu.
   *
   * @param id the identifier associated with the desired menu.
   * @since 0.1.0
   */
  virtual void SetMenu(MenuID id) = 0;

  [[nodiscard]] virtual const IMenu& GetMenu() const = 0;
};

using IMenuStateMachine_uptr = std::unique_ptr<IMenuStateMachine>;
using IMenuStateMachine_sptr = std::shared_ptr<IMenuStateMachine>;
using IMenuStateMachine_wptr = std::weak_ptr<IMenuStateMachine>;

}
