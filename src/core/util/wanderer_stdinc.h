#pragma once
#include <optional>
#include <memory>
#include <cstdint>

namespace albinjohansson::wanderer {

template<typename T>
using maybe = std::optional<T>;

template<typename T>
using unique = std::unique_ptr<T>;

template<typename T>
using shared = std::shared_ptr<T>;

template<typename T>
using weak = std::weak_ptr<T>;

using int8 = std::int_fast8_t;
using int16 = std::int_fast16_t;
using int32 = std::int_fast32_t;
using int64 = std::int_fast64_t;

using uint8 = std::uint_fast8_t;
using uint16 = std::uint_fast16_t;
using uint32 = std::uint_fast32_t;
using uint64 = std::uint_fast64_t;

}
