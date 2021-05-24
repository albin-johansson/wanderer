#pragma once

#include <chrono>  // system_clock
#include <string>  // string

namespace wanderer {

/**
 * \brief Converts a system clock time point value to a string.
 *
 * \details Example string: "Mon May 24 21:42:13 2021".
 *
 * \param timePoint
 *
 * \return the time point as a string.
 */
[[nodiscard]] auto to_string(const std::chrono::system_clock::time_point timePoint)
    -> std::string;

/**
 * \brief Returns the current time as a string.
 *
 * \ingroup core
 *
 * \return the current time using the format "HH:MM:SS".
 */
[[nodiscard]] auto current_hhmmss() -> std::string;

}  // namespace wanderer
