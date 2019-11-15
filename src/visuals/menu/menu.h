#pragma once
#include "input.h"
#include "drawable.h"
#include <memory>

namespace wanderer::visuals {

/**
 * The IMenu interface specifies objects that represent interactive menus in the game.
 *
 * @since 0.1.0
 */
class IMenu : public core::IDrawable {
 protected:
  IMenu() = default;

 public:
  ~IMenu() override = default;

  virtual void HandleInput(const core::Input& input) noexcept = 0;

  [[nodiscard]] virtual bool IsBlocking() const noexcept = 0;
};

using IMenu_uptr = std::unique_ptr<IMenu>;
using IMenu_sptr = std::shared_ptr<IMenu>;
using IMenu_wptr = std::weak_ptr<IMenu>;

}
