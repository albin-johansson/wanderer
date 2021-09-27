#pragma once

#include <centurion.hpp>  // farea, surface, texture

#include "common/entity_type.hpp"
#include "common/maybe.hpp"
#include "core/grid_position.hpp"

namespace wanderer::comp {

namespace tags {
struct lazy_texture_tag;
}  // namespace tags

/**
 * \brief Represents a texture that is lazily initialized.
 *
 * \ingroup components
 */
struct lazy_texture final
{
  using entity = entity_type<tags::lazy_texture_tag>;

  grid_position position;               ///< The position of the texture.
  cen::farea size;                      ///< The size of the rendered texture.
  cen::surface surface;                 ///< Source image data.
  mutable maybe<cen::texture> texture;  ///< The lazily initialized texture.
};

}  // namespace wanderer::comp
