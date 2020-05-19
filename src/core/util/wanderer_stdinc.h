#pragma once
#include <centurion.h>

#include <cstdint>
#include <json.hpp>
#include <memory>
#include <optional>
#include <string>

namespace albinjohansson::wanderer {

template <typename T>
using Maybe = std::optional<T>;

inline constexpr std::nullopt_t nothing = std::nullopt;

template <typename T>
using UniquePtr = std::unique_ptr<T>;

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

using JSONValue = nlohmann::json::value_type;
using JSON = nlohmann::json;

#define WANDERER_SERIALIZE_ENUM NLOHMANN_JSON_SERIALIZE_ENUM

using CZString = const char*;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

namespace ctn = centurion;

}  // namespace albinjohansson::wanderer
