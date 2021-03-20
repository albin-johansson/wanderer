#pragma once

#include <centurion.hpp>  // scan_code
#include <memory>         // unique_ptr
#include <vector>         // vector

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

struct key_bind_pack final
{
  std::vector<key_bind::entity> binds;
};

}  // namespace wanderer::comp
