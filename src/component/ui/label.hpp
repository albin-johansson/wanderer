#pragma once

#include <cen/color.hpp>    // color
#include <cen/point.hpp>    // fpoint
#include <cen/texture.hpp>  // texture
#include <string>           // string

#include "entity_type.hpp"
#include "maybe.hpp"

namespace wanderer::comp {
namespace detail {
struct label_entity_t;
}

struct label final
{
  using entity = entity_type<detail::label_entity_t>;

  cen::fpoint position;
  std::string text;
  cen::color color;
  mutable maybe<cen::texture> texture;
};

}  // namespace wanderer::comp
