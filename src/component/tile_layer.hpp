#pragma once

#include <entt.hpp>
#include <named_type.hpp>
#include <vector>

#include "tile_id.hpp"

namespace wanderer::comp {
namespace detail {
struct tile_layer_entity_t;
}

/**
 * @struct tile_layer
 *
 * @brief Represents a layer of tiles.
 *
 * @details Multiple tile layers are combined to create tilemaps.
 *
 * @headerfile tile_layer.hpp
 */
struct tile_layer final
{
  using entity = fluent::
      NamedType<entt::entity, detail::tile_layer_entity_t, fluent::Comparable>;
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix matrix; /**< Matrix of tile IDs that represent the layer. */
};

}  // namespace wanderer::comp
