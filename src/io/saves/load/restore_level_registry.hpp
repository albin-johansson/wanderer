#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer {
namespace proto {
class Level;
}  // namespace proto

[[nodiscard]] auto RestoreLevelRegistry(const proto::Level& data) -> entt::registry;

}  // namespace wanderer
