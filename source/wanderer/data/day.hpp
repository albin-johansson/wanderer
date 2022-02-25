#pragma once

#include <string_view>  // string_view

namespace wanderer {

/// \addtogroup core
/// \{

/**
 * \brief Represents the days of the week.
 */
enum class day_of_week
{
  monday,
  tuesday,
  wednesday,
  thursday,
  friday,
  saturday,
  sunday
};

/**
 * \brief Returns the full name of a day enumerator, e.g. "monday".
 *
 * \param day the day to get the name of.
 *
 * \return the full day name.
 */
[[nodiscard]] auto full_name(day_of_week day) -> std::string_view;

/**
 * \brief Returns the an abbreviated name of a day enumerator, e.g. "MON".
 *
 * \param day the day to get the name of.
 *
 * \return the abbreviated day name.
 */
[[nodiscard]] auto short_name(day_of_week day) -> std::string_view;

/// \} End of group core

}  // namespace wanderer