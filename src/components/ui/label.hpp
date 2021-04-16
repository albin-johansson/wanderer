#pragma once

#include <centurion.hpp>
#include <string>  // string
#include <vector>  // vector

#include "entity_type.hpp"
#include "maybe.hpp"
#include "text_size.hpp"

namespace wanderer::comp {
namespace detail {
struct label_entity_t;
}

struct label final
{
  using entity = entity_type<detail::label_entity_t>;

  float row;
  float col;
  std::string text;
  cen::color color;
  text_size size;

  mutable maybe<cen::texture> texture;
};

struct label_pack final
{
  std::vector<label::entity> labels;
};

}  // namespace wanderer::comp
