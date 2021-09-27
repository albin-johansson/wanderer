#pragma once

#include "common/entity_type.hpp"
#include "core/grid_position.hpp"

namespace wanderer::comp {

namespace tags {
struct line_tag;
}  // namespace tags

struct line final
{
  using entity = entity_type<tags::line_tag>;

  grid_position start;
  grid_position end;
};

}  // namespace wanderer::comp
