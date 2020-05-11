#pragma once

#include <input.h>
#include <renderer.h>

#include "menu_button.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class NewMenu {
 public:
  NewMenu(weak<IMenuStateMachine> menuStateMachine, const char* jsonFile);

  void draw(centurion::video::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const noexcept;

  void handle_input(const Input& input) noexcept;

  bool blocking() const noexcept;

 private:
  std::vector<unique<MenuButton>> m_buttons;
  bool m_blocking;
};

}  // namespace albinjohansson::wanderer
