#pragma once

#include <entt.hpp>  // registry

namespace wanderer {
namespace proto {
class level;
}  // namespace proto

[[nodiscard]] auto restore_level_registry(const proto::level& data) -> entt::registry;

}  // namespace wanderer
