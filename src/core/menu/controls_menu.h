#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include <memory>

namespace albinjohansson::wanderer {

class ControlsMenu final : public AbstractMenu {
 public:
  explicit ControlsMenu(IMenuStateMachine* parent);

  ~ControlsMenu() noexcept override;

  void Draw(centurion::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void HandleInput(const Input& input) noexcept override;

  [[nodiscard]]
  inline bool IsBlocking() const noexcept override { return true; }
};

}
