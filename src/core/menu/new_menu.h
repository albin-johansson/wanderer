#pragma once

#include <input.h>
#include <renderer.h>

#include "menu.h"
#include "menu_button.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class NewMenu : public IMenu {
 public:
  NewMenu(weak<IMenuStateMachine> menuStateMachine, const char* jsonFile);

  ~NewMenu() noexcept override = default;

  void draw(ctn::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const noexcept override;

  void handle_input(const Input& input) noexcept override;

  [[nodiscard]] bool is_blocking() const noexcept override;

 private:
  std::vector<unique<MenuButton>> m_buttons;
  bool m_blocking;
};

}  // namespace albinjohansson::wanderer
