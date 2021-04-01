#pragma once

#include <entt.hpp>
#include <named_type.hpp>

namespace wanderer {

template <typename T>
using entity_type =
    fluent::NamedType<entt::entity, T, fluent::Comparable, fluent::FunctionCallable>;

}  // namespace wanderer
