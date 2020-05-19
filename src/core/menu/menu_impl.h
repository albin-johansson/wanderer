#pragma once

#include <input.h>
#include <renderer.h>

#include <string>

#include "action_parser.h"
#include "menu.h"
#include "menu_button.h"
#include "menu_state_machine.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class MenuImpl : public IMenu {
 public:
  MenuImpl(ActionParser& actionParser, const char* jsonFile);

  ~MenuImpl() noexcept override = default;

  void draw(ctn::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const noexcept override;

  void handle_input(const Input& input) noexcept override;

  [[nodiscard]] bool is_blocking() const noexcept override
  {
    return m_blocking;
  }

 private:
  std::vector<UniquePtr<MenuButton>> m_buttons;
  std::string m_title;
  bool m_blocking;
};

}  // namespace albinjohansson::wanderer
