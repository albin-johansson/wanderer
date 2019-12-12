#pragma once
#include "abstract_menu.h"

namespace albinjohansson::wanderer {

class InventoryMenu final : public AbstractMenu {
 private:
 public:
  explicit InventoryMenu(IMenuStateMachine* parent);

  ~InventoryMenu() override;

  void HandleInput(const Input& input) noexcept override;

  [[nodiscard]] bool IsBlocking() const noexcept override;

};

}
