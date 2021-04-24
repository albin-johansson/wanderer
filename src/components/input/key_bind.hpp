#pragma once

#include <centurion.hpp>  // scan_code

#include "core/aliases/entity_type.hpp"
#include "core/menu_action.hpp"

namespace wanderer::comp {
namespace detail {
struct key_bind_t;
}

struct key_bind final
{
  using entity = entity_type<detail::key_bind_t>;

  cen::scan_code key;
  menu_action action;
};

}  // namespace wanderer::comp
