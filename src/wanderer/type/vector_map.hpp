#pragma once

#include <concepts>  // equality_comparable_with

#include <EASTL/functional.h>
#include <EASTL/vector_map.h>

#include "wanderer/core/error.hpp"
#include "wanderer/type/eastl_new.hpp"

namespace wanderer {

template <typename K, typename V>
using VectorMap = eastl::vector_map<K, V>;

template <typename K, typename V, std::equality_comparable_with<K> T>
[[nodiscard]] auto lookup_in(const VectorMap<K, V>& map, const T& key) -> const V&
{
  const auto iter = map.find_as(key, eastl::equal_to_2<K, T> {});
  if (iter != map.end()) [[likely]] {
    return iter->second;
  }
  else {
    throw Error {"Found no matching element!"};
  }
}

}  // namespace wanderer
