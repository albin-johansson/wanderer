#pragma once

#include <string>  // string
#include <vector>  // vector

#include "button.hpp"
#include "entity_type.hpp"
#include "null_entity.hpp"

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

  button::entity decrementButton{null<button>()};
  button::entity incrementButton{null<button>()};
  button::entity deleteButton{null<button>()};
  button::entity loadButton{null<button>()};
};

}  // namespace wanderer::comp
