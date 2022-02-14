#pragma once

#include <centurion.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

#undef small

namespace wanderer {

enum class font_id
{
  daniel,
  type_writer
};

enum class font_size
{
  small,
  medium,
  large
};

class graphics_ctx final
{
 public:
  explicit graphics_ctx(const game_cfg& cfg);

  [[nodiscard]] auto get_pixelated_font(font_size size) -> cen::font&;

  [[nodiscard]] auto get_handwriting_font(font_size size) -> cen::font&;

  [[nodiscard]] auto window() -> cen::window&;

  [[nodiscard]] auto renderer() -> cen::renderer&;

 private:
  cen::window mWindow;
  cen::renderer mRenderer;

  cen::font_bundle mFontBundle;
  cen::font_bundle::id_type mPixelatedFontId;
  cen::font_bundle::id_type mHandwritingFontId;
};

}  // namespace wanderer