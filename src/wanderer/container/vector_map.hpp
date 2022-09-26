#pragma once

#include <concepts>  // equality_comparable_with

#include <EASTL/algorithm.h>
#include <EASTL/vector_map.h>

#include "wanderer/container/eastl_new.hpp"
#include "wanderer/core/error.hpp"

namespace wanderer {

template <typename K, typename V>
using VectorMap = eastl::vector_map<K, V>;

template <typename K, typename V, std::equality_comparable_with<K> T>
[[nodiscard]] auto lookup_in(const VectorMap<K, V>& map, const T& key) -> const V&
{
  const auto iter = eastl::find_if(map.begin(), map.end(), [&](const auto& pair) {
    return key == pair.first;
  });

  if (iter != map.end()) [[likely]] {
    return iter->second;
  }
  else {
    throw Error {"Found no matching element!"};
  }
}

}  // namespace wanderer
