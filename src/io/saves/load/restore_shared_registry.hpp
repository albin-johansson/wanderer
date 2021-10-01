#pragma once

#include <entt.hpp>  // registry

namespace wanderer {
namespace proto {
class save;
}  // namespace proto

void restore_shared_registry(entt::registry& shared, const proto::save& save);

}  // namespace wanderer