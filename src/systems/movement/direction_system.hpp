#pragma once

#include "components/movable.hpp"
#include "core/direction.hpp"

namespace wanderer::sys {

/// \name Movement
/// \{

/**
 * \brief Returns the appropriate dominant direction for a movable component.
 *
 * \ingroup systems
 *
 * \param movable the movable component that will be used.
 *
 * \return the calculated dominant direction for the movable.
 *
 * \since 0.1.0
 */
[[nodiscard]] auto dominant_direction(const comp::movable& movable) noexcept -> direction;

/// \} End of movement

}  // namespace wanderer::sys
