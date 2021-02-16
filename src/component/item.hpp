#pragma once

#include "entity_type.hpp"
#include "texture_handle.hpp"

namespace wanderer::comp {
namespace detail {
struct item_entity_t;
}

struct item final
{
  using entity = entity_type<detail::item_entity_t>;
  texture_handle texture;
};

}  // namespace wanderer::comp
