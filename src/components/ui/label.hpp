#pragma once

#include <centurion.hpp>  // color, texture
#include <string>         // string

#include "core/aliases/entity_type.hpp"
#include "core/aliases/maybe.hpp"
#include "core/grid_position.hpp"
#include "core/text_size.hpp"

namespace wanderer::comp {
namespace detail {
struct label_entity_t;
}

struct label final
{
  using entity = entity_type<detail::label_entity_t>;

  grid_position position;
  std::string text;
  cen::color color;
  text_size size{};

  mutable maybe<cen::texture> texture;
};

}  // namespace wanderer::comp
