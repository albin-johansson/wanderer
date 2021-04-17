#pragma once

#include "core/aliases/entity_type.hpp"
#include "core/aliases/ints.hpp"

namespace wanderer::comp {
namespace detail {
struct object_entity_t;
}

struct object final
{
  using entity = entity_type<detail::object_entity_t>;

  int id;
};

void serialize(auto& archive, object& o, u32 version)
{
  archive(o.id);
}

}  // namespace wanderer::comp
