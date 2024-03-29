#pragma once

#include <vector>  // vector

#include <glm/glm.hpp>

#include "wanderer/common.hpp"

namespace wanderer::comp {

/// \addtogroup components
/// \{

/**
 * \brief Represents a layer of static tiles.
 */
struct TileLayer final
{
  using tile_row = std::vector<tile_id>;
  using tile_matrix = std::vector<std::vector<tile_id>>;

  tile_matrix tiles;  ///< The tile data.
  int32 z{};          ///< Rendering depth index.
};

/**
 * \brief Component featured by tile objects, i.e. non-empty tiles in non-ground layers.
 */
struct TileObject final
{
  entt::entity tile_entity{entt::null};  ///< The associated tile info entity.
};

/**
 * \brief Provides information about a single tilemap, which consists of several layers.
 */
struct Tilemap final
{
  int32 humanoid_layer_index{};  ///< The layer index inhabited by humanoids.
  usize row_count{};             ///< Total amount of tile rows.
  usize col_count{};             ///< Total amount of tile columns.
  glm::vec2 size{};              ///< Map size in pixels.
};

/**
 * \brief Component describing the hitbox of a tile.
 */
struct TileHitbox final
{
  glm::vec2 offset{};  ///< Offset from origin in the parent tile.
  glm::vec2 size{};    ///< The size of the hitbox.
};

/**
 * \brief Provides information about a tile in a tileset.
 */
struct TileInfo final
{
  texture_id texture{};  ///< Associated tileset texture.
  int32 depth_index{};   ///< The rendering depth index.
  glm::ivec4 source{};   ///< The region of the source tileset that represents the tile.
};

/**
 * \brief Provides information about all available tiles in a level.
 */
struct Tileset final
{
  hash_map<tile_id, entt::entity> tiles;

  /**
   * \brief A frame-by-frame cache that maps tile entities to rendered tile entities.
   */
  mutable hash_map<entt::entity, entt::entity> effective_appearance;
};

/// \} End of group components

}  // namespace wanderer::comp