#pragma once

#include "core/aliases/entity_type.hpp"

namespace wanderer::comp {

namespace tags {
struct checkbox_tag;
}  // namespace tags

struct checkbox final
{
  using entity = entity_type<tags::checkbox_tag>;

  bool checked{};
};

}  // namespace wanderer::comp
