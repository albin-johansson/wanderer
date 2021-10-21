#pragma once

#include <entt.hpp>  // registry

namespace wanderer {
namespace proto {
class level;
}  // namespace proto

[[nodiscard]] auto RestoreLevelRegistry(const proto::level& data) -> entt::registry;

}  // namespace wanderer
