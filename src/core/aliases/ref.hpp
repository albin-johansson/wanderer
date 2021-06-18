#pragma once

#include <functional>  // reference_wrapper

namespace wanderer {

template <typename T>
using ref = std::reference_wrapper<T>;

}  // namespace wanderer
