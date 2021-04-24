#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/grid_position.hpp"

namespace wanderer::comp {
namespace detail {
struct line_t;
}

struct line final
{
  using entity = entity_type<detail::line_t>;

  grid_position start;
  grid_position end;
};

}  // namespace wanderer::comp
