#pragma once

#include <entt.hpp>  // registry

#include "core/serialization.hpp"

namespace wanderer::sys {

/// \name Saves
/// \{

/**
 * \brief Saves a snapshot of the supplied registry.
 *
 * \ingroup systems
 *
 * \param registry the registry that will be saved.
 * \param archive the output serialization archive that will be used.
 */
void save_registry(const entt::registry& registry, output_archive& archive);

/**
 * \brief Creates a registry based on a previously serialized registry.
 *
 * \ingroup systems
 *
 * \param archive the input archive that provides the serialized registry data.
 *
 * \return the restored registry.
 */
[[nodiscard]] auto restore_registry(input_archive& archive) -> entt::registry;

/// \} End of saves

}  // namespace wanderer::sys
