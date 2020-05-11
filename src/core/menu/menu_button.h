#pragma once
#include <action.h>
#include <rectangle.h>
#include <texture.h>

#include <memory>
#include <string>

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
  MenuButton(std::string text,
             centurion::math::FRect bounds,
             unique<IAction> action);

  ~MenuButton() override;

  void draw(centurion::video::Renderer& renderer,
            const Viewport& viewport,
            const FontBundle& fonts) const override;

  void set_enlarged(bool enlarged) noexcept;

  void trigger() noexcept;

  [[nodiscard]] bool contains(float mx, float my) const noexcept;

 private:
  centurion::math::FRect m_bounds;
  unique<IAction> m_action;
  // FIXME why does all button have unique textures? share them!
  mutable unique<centurion::video::Texture> m_normalImg = nullptr;
  mutable unique<centurion::video::Texture> m_enlargedImg = nullptr;

  const std::string m_text = "";
  bool m_enlarged = false;

  void render_text(const centurion::video::Renderer& renderer,
                   float x,
                   float y,
                   unique<centurion::video::Texture>& img,
                   const centurion::video::Font& font) const;
};

}  // namespace albinjohansson::wanderer
