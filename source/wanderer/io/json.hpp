#pragma once

#include <nlohmann/json.hpp>

namespace wanderer {

/**
 * \brief Attempts to parse a JSON file.
 *
 * \param path the file path to the source JSON file.
 *
 * \return a JSON object.
 *
 * \throws wanderer_error if something goes wrong.
 */
[[nodiscard]] auto read_json(const std::filesystem::path& path) -> nlohmann::json;

}  // namespace wanderer
