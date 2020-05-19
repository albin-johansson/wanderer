#pragma once

#include <input.h>

#include "key_bind.h"
#include "menu.h"
#include "menu_button.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class MenuImpl final : public IMenu {
 public:
  friend class MenuParser;

  ~MenuImpl() noexcept = default;

  void draw(ctn::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const noexcept override;

  void handle_input(const Input& input) noexcept override;

  [[nodiscard]] bool is_blocking() const noexcept override
  {
    return m_blocking;
  }

 private:
  MenuImpl();

  std::vector<UniquePtr<MenuButton>> m_buttons;
  std::vector<UniquePtr<KeyBind>> m_binds;
  std::string m_title = "";
  bool m_blocking = false;
};

}  // namespace albinjohansson::wanderer
