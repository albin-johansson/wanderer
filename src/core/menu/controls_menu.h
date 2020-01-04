#pragma once
#include "abstract_menu.h"
#include "menu_state_machine.h"
#include <memory>

namespace albinjohansson::wanderer {

class ControlsMenu final : public AbstractMenu {
 public:
  explicit ControlsMenu(IMenuStateMachine* parent);

  ~ControlsMenu() noexcept override;

  void draw(centurion::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void handle_input(const Input& input) noexcept override;

  [[nodiscard]]
  inline bool is_blocking() const noexcept override { return true; }
};

}
