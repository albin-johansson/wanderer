#ifndef INIT_COMMON_HPP
#define INIT_COMMON_HPP

#include <cstddef>  // size_t
#include <cstdint>  // uint{}_t, int{}_t

namespace init {

using usize = std::size_t;
using ulonglong = unsigned long long;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

}  // namespace init

#endif  // INIT_COMMON_HPP