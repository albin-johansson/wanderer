#pragma once

#include <centurion.hpp>
#include <memory>  // unique_ptr

#include "action.hpp"
#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct key_bind_entity_t;
}

struct key_bind final
{
  using entity = entity_type<detail::key_bind_entity_t>;

  cen::scan_code key;
  std::unique_ptr<action> action;
};

}  // namespace wanderer::comp
