#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer {
namespace proto {
class Save;
}  // namespace proto

void RestoreSharedRegistry(entt::registry& shared, const proto::Save& save);

}  // namespace wanderer