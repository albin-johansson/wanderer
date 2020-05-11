#pragma once
#include <action.h>
#include <rect.h>
#include <texture.h>

#include <memory>
#include <string>

#include "drawable_text.h"
#include "menu_drawable.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

/**
 * The MenuButton class is a simple representation of a graphical button.
 *
 * @since 0.1.0
 */
class MenuButton final : public IMenuDrawable {
 public:
  /**
   * @param text the text of the button.
   * @param bounds the rectangle that represents the position and size of the
   * button.
   * @param action the action that will be executed when the button is
   * triggered.
   * @since 0.1.0
   */
  MenuButton(std::string text, ctn::FRect bounds, unique<IAction> action);

  ~MenuButton() override;

  void draw(ctn::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void set_enlarged(bool enlarged) noexcept;

  void trigger() noexcept;

  [[nodiscard]] bool contains(float mx, float my) const noexcept;

 private:
  ctn::FRect m_bounds;
  unique<IAction> m_action;
  std::unique_ptr<DrawableText> m_text;
  bool m_enlarged = false;
};

}  // namespace albinjohansson::wanderer
