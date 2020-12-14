#pragma once

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct object_entity_t;
}

struct object final
{
  using entity = entity_type<detail::object_entity_t>;
  int id;
};

}  // namespace wanderer::comp
