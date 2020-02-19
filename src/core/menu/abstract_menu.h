#pragma once
#include "menu.h"
#include "menu_state_machine.h"

namespace albinjohansson::wanderer {

class AbstractMenu : public IMenu {
 protected:
  IMenuStateMachine* parent = nullptr;

  explicit AbstractMenu(IMenuStateMachine* parent);

 public:
  ~AbstractMenu() noexcept override;

  void draw(centurion::video::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;
};

}  // namespace albinjohansson::wanderer
