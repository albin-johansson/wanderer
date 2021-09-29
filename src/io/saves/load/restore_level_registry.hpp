#pragma once

#include <entt.hpp>  // registry

namespace wanderer {
namespace protobuf {
class level;
}  // namespace protobuf

[[nodiscard]] auto restore_level_registry(const protobuf::level& data) -> entt::registry;

}  // namespace wanderer
