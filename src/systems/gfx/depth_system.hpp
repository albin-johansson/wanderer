#pragma once

#include <entt/entt.hpp>  // registry

namespace wanderer::sys {

/// \name Depth
/// \{

enum class SortStrategy
{
  InsertionSort,  ///< Better choice when most elements are already sorted.
  StdSort         ///< Performs well with unsorted collections.
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
void UpdateDepth(entt::registry& registry,
                 SortStrategy strategy = SortStrategy::InsertionSort);

/// \} End of depth

}  // namespace wanderer::sys
