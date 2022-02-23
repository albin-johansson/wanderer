#pragma once

#include <entt/entt.hpp>

#include "wanderer/common.hpp"
#include "wanderer/fwd.hpp"

namespace wanderer::sys {

/**
 * \ingroup systems
 * \defgroup rendering-system
 *
 * \brief Covers the main rendering logic.
 *
 * \todo Merge viewport system into this system?
 */

/// \addtogroup rendering-system
/// \{

/**
 * \brief Represents different approaches to sorting.
 */
enum class sort_strategy
{
  std,       ///< Use std::sort, which works well with large sets of unsorted data.
  insertion  ///< Use insertion sort, works well when the data is almost sorted.
};

/**
 * \brief Sorts all drawable entities.
 *
 * \param registry the level registry.
 * \param strategy the strategy used for sorting.
 */
void sort_drawables(entt::registry& registry, sort_strategy strategy);

/**
 * \brief Renders all visible drawable entities.
 *
 * \details Remember to call `sort_drawables()` before this function.
 *
 * \param registry the level registry.
 * \param graphics the current graphics context.
 */
void render_drawables(const entt::registry& registry, graphics_ctx& graphics);

/// \} End of group rendering-system

}  // namespace wanderer::sys
