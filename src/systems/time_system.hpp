#pragma once

#include <entt.hpp>  // registry, dispatcher

namespace wanderer::sys {

/// \name Time
/// \{

[[nodiscard]] constexpr auto HourToSeconds(const float hour) noexcept -> float
{
  return hour * 3'600.0f;
}

/**
 * \brief Updates the state of the time.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry, since levels share their time data.
 * \param dispatcher the event dispatcher that will be used.
 * \param dt the current delta time.
 *
 * \see `ctx::TimeOfDay`
 */
void UpdateTime(entt::registry& shared, entt::dispatcher& dispatcher, float dt);

/**
 * \brief Changes the time to the next day.
 *
 * \ingroup systems
 *
 * \param shared the shared data registry.
 * \param dispatcher the event dispatcher that will be used.
 * \param hour the hour to start the next day at.
 */
void ChangeToNextDay(entt::registry& shared,
                     entt::dispatcher& dispatcher,
                     float hour = 0);

/**
 * \brief Renders a digital clock in the upper left corner of the screen with the current
 * time.
 *
 * \ingroup systems
 *
 * \param registry the shared data registry, since levels share their time data.
 */
void RenderClock(const entt::registry& registry);

/// \} End of time

}  // namespace wanderer::sys
