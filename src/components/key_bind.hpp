#pragma once

#include <centurion.hpp>  // scan_code

#include "core/aliases/entity_type.hpp"
#include "core/menu_action.hpp"

namespace wanderer::comp {

namespace tags {
struct key_bind_tag;
}  // namespace tags

struct key_bind final
{
  using entity = entity_type<tags::key_bind_tag>;

  cen::scan_code key;
  menu_action action{menu_action::none};
};

}  // namespace wanderer::comp
