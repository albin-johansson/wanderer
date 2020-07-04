/**
 * @brief Provides the AABB system.
 * @file aabb_system.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <area.h>
#include <point.h>

#include "aabb.h"
#include "wanderer_stdinc.h"

/**
 * @namespace wanderer::sys::aabb
 * @brief Provides the AABB system.
 */
namespace wanderer::sys::aabb {

/**
 * @brief Creates and returns an AABB instance.
 *
 * @details This is a convenience method that handles the calculation of the
 * center point and area of the created box.
 *
 * @param pos the position of the box.
 * @param size the size of the box.
 * @return the created AABB instance.
 */
[[nodiscard]] auto make_aabb(const ctn::FPoint& pos,
                             const ctn::FArea& size) noexcept -> comp::AABB;

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
 * @brief Indicates whether or not two AABBs overlap.
 *
 * @param fst the first box.
 * @param snd the second box.
 * @return `true` if the boxes overlap; `false` otherwise.
 */
[[nodiscard]] auto overlaps(const comp::AABB& fst,
                            const comp::AABB& snd) noexcept -> bool;

/**
 * @brief Inserts an AABB instance into the AABB tree.
 *
 * @param registry the associated registry.
 * @param box the AABB instance that will be inserted.
 * @return the entity identifier associated with the supplied box.
 */
auto insert(entt::registry& registry, const comp::AABB& box) noexcept
    -> entt::entity;

// used to obtain collision candidates, could invoke some callback
void query(entt::registry& registry, const entt::entity entity);

}  // namespace wanderer::sys::aabb
