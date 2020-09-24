#pragma once

#include <named_type.hpp>
#include <unordered_map>  // unordered_map
#include <vector>         // vector

#include "map_position.hpp"
#include "null_entity.hpp"
#include "tile_layer.hpp"
#include "tileset.hpp"

namespace wanderer::comp {
namespace detail {
struct tilemap_entity_t;
}

/**
 * @struct tilemap
 *
 * @brief Represents a tilemap (a level in the game).
 *
 * @var tilemap::tileset
 * The associated tileset.
 * @var tilemap::layers
 * The tile layers in the map.
 * @var tilemap::tileObjects
 * The tile objects in the map.
 * @var tilemap::width
 * The width of the tilemap, in pixels.
 * @var tilemap::height
 * The height of the tilemap, in pixels.
 * @var tilemap::rows
 * The amount of rows in the tilemap.
 * @var tilemap::cols
 * The amount of columns in the tilemap.
 *
 * @headerfile tilemap.hpp
 */
struct tilemap final
{
  using entity = fluent::
      NamedType<entt::entity, detail::tilemap_entity_t, fluent::Comparable>;

  comp::tileset::entity tileset = null<comp::tileset>();
  std::vector<tile_layer::entity> layers;

  // TODO use tile object entity tag type
  std::unordered_map<map_position, entt::entity> tileObjects;

  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer::comp
