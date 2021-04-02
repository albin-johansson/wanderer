#pragma once

#include <centurion.hpp>
#include <vector>  // vector

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

struct line_pack final
{
  std::vector<line::entity> lines;
};

}  // namespace wanderer::comp
