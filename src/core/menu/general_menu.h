#pragma once
#include <memory>
#include <vector>

#include "menu.h"
#include "menu_button.h"

namespace albinjohansson::wanderer {

class GeneralMenu final : public IMenu {
 private:
  bool blocking = true;
  std::vector<std::unique_ptr<MenuButton>> buttons;

 public:
  ~GeneralMenu() noexcept override = default;

  void draw(centurion::video::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void handle_input(const Input& input) noexcept override;

  void set_blocking(bool blocking) noexcept;

  void set_buttons(std::vector<std::unique_ptr<MenuButton>>&& buttons);

  [[nodiscard]] bool is_blocking() const noexcept override;
};

}  // namespace albinjohansson::wanderer
