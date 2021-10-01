#pragma once

#include <entt.hpp>  // registry

namespace wanderer::sys {

/// \name Depth
/// \{

enum class sort_strategy
{
  insertion_sort,  ///< Better choice when most elements are already sorted.
  std_sort         ///< Performs well with unsorted collections.
};

/**
 * \brief Sorts all depth drawables.
 *
 * \ingroup systems
 *
 * \param registry the current level registry.
 * \param strategy the sorting strategy that will be used.
 *
 * \since 0.1.0
 */
void update_depth(entt::registry& registry,
                  sort_strategy strategy = sort_strategy::insertion_sort);

/// \} End of depth

}  // namespace wanderer::sys
