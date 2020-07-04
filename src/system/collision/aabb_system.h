#pragma once

#include <area.h>
#include <point.h>

#include "aabb.h"
#include "wanderer_stdinc.h"

namespace wanderer::sys::aabb {

/**
 * @brief Returns an AABB for the supplied boxes.
 *
 * @details Creates and returns an AABB that is sized to encapsulate both of
 * the supplied boxes.
 *
 * @param fst the first AABB.
 * @param snd the second AABB.
 * @return an AABB that is the merged result of the two supplied boxes.
 */
[[nodiscard]] auto merge(const comp::AABB& fst, const comp::AABB& snd) noexcept
    -> comp::AABB;

/**
 * @brief
 *
 * @param pos
 * @param size
 * @return
 */
[[nodiscard]] auto make_aabb(const ctn::FPoint& pos,
                             const ctn::FArea& size) noexcept -> comp::AABB;

auto overlaps(const comp::AABB& fst, const comp::AABB& snd) -> bool;

void insert(entt::registry& registry,
            entt::entity entity,
            const comp::AABB& box);

// used to obtain collision candidates, could invoke some callback
void query(entt::registry& registry, const entt::entity entity);

}  // namespace wanderer::sys::aabb
