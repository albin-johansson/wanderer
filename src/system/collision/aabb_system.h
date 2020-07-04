#pragma once

#include <area.h>
#include <point.h>

#include "aabb.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::aabb {

auto merge(const comp::AABB& fst, const comp::AABB& snd) -> comp::AABB;

auto create_box(const ctn::FPoint& pos, const ctn::FArea& size) noexcept
    -> comp::AABB;

auto overlaps(const comp::AABB& fst, const comp::AABB& snd) -> bool;

void insert(entt::registry& registry,
            entt::entity entity,
            const comp::AABB& box);

// used to obtain collision candidates, could invoke some callback
void query(entt::registry& registry, const entt::entity entity);

}  // namespace wanderer::sys::aabb
