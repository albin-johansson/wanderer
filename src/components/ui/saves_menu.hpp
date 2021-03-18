#pragma once

#include <string>  // string
#include <vector>  // vector

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct saves_menu_entity_t;
struct saves_menu_entry_entity_t;
}  // namespace detail

struct saves_menu_entry final
{
  using entity = entity_type<detail::saves_menu_entry_entity_t>;

  std::string name;
};

struct saves_menu final
{
  using entity = entity_type<detail::saves_menu_entity_t>;

  std::vector<saves_menu_entry::entity> entries;
};

}  // namespace wanderer::comp
