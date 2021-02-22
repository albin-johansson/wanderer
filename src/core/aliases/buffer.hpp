#pragma once

#include <array>    // array
#include <cstddef>  // byte

namespace wanderer {

template <typename T, std::size_t amount>
using buffer_t = std::array<std::byte, amount * sizeof(T)>;

}  // namespace wanderer
