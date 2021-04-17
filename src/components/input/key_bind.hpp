#pragma once

#include <centurion.hpp>  // scan_code
#include <vector>         // vector

#include "core/aliases/entity_type.hpp"
#include "core/menu_action.hpp"

namespace wanderer::comp {
namespace detail {
struct key_bind_entity_t;
}

struct key_bind final
{
  using entity = entity_type<detail::key_bind_entity_t>;

  cen::scan_code key;
  menu_action action;
};

struct key_bind_pack final
{
  std::vector<key_bind::entity> binds;
};

}  // namespace wanderer::comp
