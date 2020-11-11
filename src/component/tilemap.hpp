#pragma once

#include <named_type.hpp>
#include <unordered_map>  // unordered_map
#include <vector>         // vector

#include "entity_type.hpp"
#include "map_position.hpp"
#include "null_entity.hpp"
#include "tile_layer.hpp"
#include "tileset.hpp"

namespace wanderer::comp {
namespace detail {
struct tilemap_entity_t;
}

/**
 * \struct tilemap
 *
 * \brief Represents a tilemap (a level in the game).
 *
 * \var tilemap::tileset
 * The associated tileset.
 * \var tilemap::tileObjects
 * The tile objects in the map.
 * \var tilemap::width
 * The width of the tilemap, in pixels.
 * \var tilemap::height
 * The height of the tilemap, in pixels.
 * \var tilemap::rows
 * The amount of rows in the tilemap.
 * \var tilemap::cols
 * The amount of columns in the tilemap.
 *
 * \headerfile tilemap.hpp
 */
struct tilemap final
{
  using entity = entity_type<detail::tilemap_entity_t>;

  // clang-format off
  [[deprecated("Use tileset::entity member of level class instead.")]]
  comp::tileset::entity tileset{null<comp::tileset>()};
  // clang-format on

  // TODO use tile object entity tag type
  std::unordered_map<map_position, entt::entity> tileObjects;

  float width;
  float height;
  int rows;
  int cols;
};

}  // namespace wanderer::comp
