#pragma once

#include <vector>  // vector

#include "entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct checkbox_entity_t;
}  // namespace detail

struct checkbox final
{
  using entity = entity_type<detail::checkbox_entity_t>;

  bool checked;
};

struct checkbox_pack final
{
  std::vector<checkbox::entity> checkboxes;
};

}  // namespace wanderer::comp
