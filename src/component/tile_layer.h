/**
 * @brief Provides the `TileLayer` component.
 * @file tile_layer.h
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <named_type.hpp>
#include <vector>

#include "wanderer_stdinc.h"

namespace wanderer::component {

/**
 * @brief Represents a layer of tiles.
 * @details Multiple tile layers are combined to create tilemaps.
 * @struct TileLayer
 * @headerfile tile_layer.h
 */
struct TileLayer final {
  using entity = fluent::
      NamedType<entt::entity, struct TileLayerEntityTag, fluent::Comparable>;
  using TileMatrix = std::vector<std::vector<TileID>>;

  TileMatrix matrix; /**< Matrix of tile IDs that represent the layer. */
};

}  // namespace wanderer::component
