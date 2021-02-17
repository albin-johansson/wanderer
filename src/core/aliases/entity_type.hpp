#pragma once

#include <entt.hpp>
#include <named_type.hpp>

namespace wanderer {

template <typename T>
using entity_type = fluent::
    NamedType<entt::entity, T, fluent::Comparable, fluent::FunctionCallable>;

}  // namespace wanderer

namespace fluent {

template <typename Archive,
          typename T,
          typename Parameter,
          template <typename>
          class... Skills>
void serialize(Archive& archive, NamedType<T, Parameter, Skills...>& n)
{
  archive(n.get());
}

}  // namespace fluent
