#pragma once

#include <centurion.hpp>  // farea, surface, texture

#include "common/maybe.hpp"
#include "core/grid_position.hpp"

namespace wanderer::comp {

/// Represents a texture that is lazily initialized.
struct lazy_texture final
{
  grid_position position;               ///< The position of the texture.
  cen::farea size;                      ///< The size of the rendered texture.
  cen::surface surface;                 ///< Source image data.
  mutable maybe<cen::texture> texture;  ///< The lazily initialized texture.
};

}  // namespace wanderer::comp
