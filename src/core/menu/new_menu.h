#pragma once

#include <input.h>
#include <renderer.h>

#include "menu_button.h"

namespace albinjohansson::wanderer {

class NewMenu {
 public:
  NewMenu(const char* jsonFile);

  void draw(centurion::video::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const noexcept;

  void handle_input(const Input& input) noexcept;

  bool blocking() const noexcept;

 private:
  std::vector<std::unique_ptr<MenuButton>> m_buttons;
  bool m_blocking;
};

}  // namespace albinjohansson::wanderer
