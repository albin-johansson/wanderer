#pragma once

#include <entt.hpp>  // registry

namespace wanderer {
namespace protobuf {
class save;
}  // namespace protobuf

void restore_shared_registry(entt::registry& shared, const protobuf::save& save);

}  // namespace wanderer