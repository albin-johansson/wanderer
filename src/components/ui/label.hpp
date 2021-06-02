#pragma once

#include <centurion.hpp>  // color, texture
#include <string>         // string

#include "core/aliases/entity_type.hpp"
#include "core/aliases/maybe.hpp"
#include "core/grid_position.hpp"
#include "core/text_size.hpp"

namespace wanderer::comp {

namespace tags {
struct label_tag;
}  // namespace tags

struct label final
{
  using entity = entity_type<tags::label_tag>;

  grid_position position;
  std::string text;
  cen::color color;
  text_size size{};

  mutable maybe<cen::texture> texture;
};

}  // namespace wanderer::comp
