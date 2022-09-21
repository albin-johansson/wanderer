#pragma once

#include <cstddef>  // size_t
#include <cstdint>  // int{}_t, uint{}_t
#include <memory>   // unique_ptr, shared_ptr, weak_ptr

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace wanderer {

using uint8 = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using int8 = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using float32 = float;
using float64 = double;

static_assert(sizeof(float32) == 4);
static_assert(sizeof(float64) == 8);

using Vec2 = glm::vec<2, float32>;
using Vec3 = glm::vec<3, float32>;
using Vec4 = glm::vec<4, float32>;

using Vec2i = glm::vec<2, int32>;
using Vec3i = glm::vec<3, int32>;
using Vec4i = glm::vec<4, int32>;

template <typename T>
using Unique = std::unique_ptr<T>;

template <typename T>
using Shared = std::shared_ptr<T>;

template <typename T>
using Weak = std::weak_ptr<T>;

}  // namespace wanderer
