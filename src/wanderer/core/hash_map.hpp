#pragma once

#include <unordered_map>  // unordered_map

namespace wanderer {

template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

}  // namespace wanderer
