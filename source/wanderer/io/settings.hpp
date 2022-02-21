#pragma once

#include "wanderer/common.hpp"

namespace wanderer {

/**
 * \brief Represents persistent game settings.
 */
struct settings final
{
  inline static constexpr uint32 fullscreen_bit = 1u << 0u;

  /**
   * \brief Bit mask of all boolean settings.
   */
  uint64 flags{};

  /**
   * \brief Sets the value of a boolean setting.
   *
   * \param flag the boolean setting bit.
   * \param value the new value of the setting.
   */
  void set_flag(uint64 flag, bool value) noexcept;

  /**
   * \brief Returns the value of a boolean setting.
   *
   * \param flag the boolean setting flag to query.
   *
   * \return `true` if the setting is enabled; `false` otherwise.
   */
  [[nodiscard]] auto test_flag(uint64 flag) const noexcept -> bool;
};

/**
 * \brief Loads settings from the persistent file directory.
 *
 * \details The default settings are returned if no settings file is found.
 *
 * \return the loaded settings.
 */
[[nodiscard]] auto load_settings() -> settings;

/**
 * \brief Saves settings to the persistent file directory.
 *
 * \param s the settings that will be saved.
 */
void save_settings(const settings& s);

}  // namespace wanderer
