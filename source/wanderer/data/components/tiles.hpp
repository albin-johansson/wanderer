#pragma once

#include <vector>  // vector

#include <glm/glm.hpp>

#include "wanderer/common.hpp"

namespace wanderer::comp {

using tile_matrix = std::vector<std::vector<tile_id>>;

/**
 * \brief Represents a layer of static tiles.
 */
struct tile_layer final
{
  tile_matrix tiles;  ///< The tile data.
};

/**
 * \brief Provides information about a single tilemap, which consists of several layers.
 */
struct tilemap final
{
  int32 humanoid_layer_index{};  ///< The layer index inhabited by humanoids.
  usize row_count{};             ///< Total amount of tile rows.
  usize col_count{};             ///< Total amount of tile columns.
};

/**
 * \brief Provides information about a tile in a tileset.
 */
struct tile_info final
{
  texture_id texture{};  ///< Associated tileset texture.
  int32 depth_index{};   ///< The rendering depth index.
  glm::ivec4 source{};   ///< The region of the source tileset that represents the tile.
};

/**
 * \brief Provides information about all of the tilesets associated with a map.
 */
struct tilesets final
{
  hash_map<tile_id, entt::entity> tiles;
};

}  // namespace wanderer::comp