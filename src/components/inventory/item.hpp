#pragma once

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct item_entity_t;
}

struct item final
{
  using entity = entity_type<detail::item_entity_t>;
  // TODO include texture_id
};

// TODO make serializable

}  // namespace wanderer::comp
