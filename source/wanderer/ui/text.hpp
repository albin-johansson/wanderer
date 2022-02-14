#pragma once

#include <string>  // string

#include <centurion.hpp>
#include <glm/glm.hpp>

#include "wanderer/common.hpp"
#include "wanderer/core/graphics.hpp"

namespace wanderer {

/**
 * \brief A lazily initialized text label.
 */
class ui_text final
{
 public:
  inline constexpr static int centered = -1;

  /**
   * \brief Creates a label.
   *
   * \param text the label text.
   * \param size the size of the label text.
   */
  ui_text(std::string text, font_size size);

  /**
   * \brief Renders the text to a texture, but does not render the label to the screen.
   *
   * \param graphics the graphics context that will be used.
   */
  void init(graphics_ctx& graphics);

  /**
   * \brief Renders the text, initializing it automatically if necessary.
   *
   * \param graphics the graphics context that will be used.
   * \param pos the position of the rendered text.
   */
  void render(graphics_ctx& graphics, const glm::vec2& pos);

  /**
   * \brief Indicates whether the text has been rendered to a texture.
   *
   * \return `true` if the label is initialized; `false` otherwise.
   */
  [[nodiscard]] auto is_initialized() const -> bool;

  /**
   * \brief Returns the size of the rendered text.
   *
   * \return the rendered text dimensions.
   */
  [[nodiscard]] auto get_size() const -> const maybe<cen::iarea>&;

 private:
  std::string mText;
  font_size mFontSize;
  maybe<cen::texture> mTexture;
  maybe<cen::iarea> mTextureSize;
};

}  // namespace wanderer