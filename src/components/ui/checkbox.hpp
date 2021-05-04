#pragma once

#include "core/aliases/entity_type.hpp"

namespace wanderer::comp {
namespace detail {
struct checkbox_entity_t;
}  // namespace detail

struct checkbox final
{
  using entity = entity_type<detail::checkbox_entity_t>;

  bool checked{};
};

}  // namespace wanderer::comp
