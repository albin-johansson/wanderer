/**
 * @brief Provides the `Tilemap` component.
 * @file tilemap.hpp
 * @author Albin Johansson
 * @copyright MIT License
 * @date 2020
 */

#pragma once

#include <named_type.hpp>
#include <unordered_map>
#include <vector>

#include "map_position.hpp"
#include "tile_layer.hpp"
#include "tileset.hpp"
#include "wanderer_stdinc.hpp"

namespace wanderer::comp {

/**
 * @struct Tilemap
 * @brief Represents a tilemap (a level in the game).
 *
 * @var Tilemap::tileset
 * The associated tileset.
 * @var Tilemap::layers
 * The tile layers in the map.
 * @var Tilemap::tileObjects
 * The tile objects in the map.
 * @var Tilemap::width
 * The width of the tilemap, in pixels.
 * @var Tilemap::height
 * The height of the tilemap, in pixels.
 * @var Tilemap::rows
 * The amount of rows in the tilemap.
 * @var Tilemap::cols
 * The amount of columns in the tilemap.
 *
 * @headerfile tilemap.hpp
 */
struct Tilemap final
{
  using entity = fluent::
      NamedType<entt::entity, struct TilemapEntityTag, fluent::Comparable>;

  comp::tileset::entity tileset = null<comp::tileset>();
  std::vector<TileLayer::entity> layers;

  // TODO use tile object entity tag type
  std::unordered_map<MapPosition, entt::entity> tileObjects;

  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer::comp
