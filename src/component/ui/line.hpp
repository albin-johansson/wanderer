#pragma once

#include <cen/point.hpp>  // fpoint

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct line_entity_t;
}

struct line final
{
  using entity = entity_type<detail::line_entity_t>;

  cen::fpoint start;
  cen::fpoint end;
};

}  // namespace wanderer::comp
