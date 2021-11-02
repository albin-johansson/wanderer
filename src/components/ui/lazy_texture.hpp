#pragma once

#include <centurion.hpp>  // farea, surface, texture

#include "core/grid_position.hpp"
#include "wanderer_std.hpp"

namespace wanderer {

/// Represents a texture that is lazily initialized.
struct LazyTexture final
{
  GridPosition position;                ///< The position of the texture.
  cen::farea size;                      ///< The size of the rendered texture.
  cen::surface surface;                 ///< Source image data.
  mutable maybe<cen::texture> texture;  ///< The lazily initialized texture.
};

}  // namespace wanderer
