#pragma once

#include <centurion.hpp>  // irect, frect
#include <map>            // map
#include <string>         // string
#include <vector>         // vector

#include "components/graphics/animated_tile.hpp"
#include "components/graphics/depth_drawable.hpp"
#include "components/graphics/point_light.hpp"
#include "components/hitbox.hpp"
#include "components/inventory/container_trigger.hpp"
#include "components/inventory/inventory.hpp"
#include "components/map/portal.hpp"
#include "components/map/spawnpoint.hpp"
#include "components/map/tile_layer.hpp"
#include "components/map/tile_object.hpp"
#include "components/object.hpp"
#include "core/aliases/depth.hpp"
#include "core/aliases/maybe.hpp"
#include "core/aliases/texture_id.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::ir {

struct texture final
{
  texture_id id;
  std::string path;  // String because it's easier to serialize
};

struct fancy_tile final
{
  depth_t depth{5};                      ///< Render depth index.
  maybe<comp::hitbox> hitbox;            ///< Optional hitbox "template".
  maybe<comp::animated_tile> animation;  ///< Optional tile animation.
};

struct tile final
{
  tile_id id{0};  ///< Unique ID.
  texture_id texture;
  cen::irect source;        ///< Source rectangle in the tileset texture.
  maybe<fancy_tile> fancy;  ///< Optional fancy features.
};

struct tileset final
{
  texture sheet;
  std::map<tile_id, tile> tiles;  ///< Tiles in the tileset.
  float xRatio;
  float yRatio;
};

struct depth_drawable final
{
  texture_id texture;
  cen::irect src;
  cen::frect dst;

  int layer{};
  depth_t depth{5};
  float centerY{};
};

struct object final
{
  int id{};                              ///< Unique object ID.
  maybe<comp::hitbox> hitbox;            ///< Optional hitbox.
  maybe<comp::depth_drawable> drawable;  ///< Optional drawable.
  maybe<comp::spawnpoint> spawnpoint;    ///< Optional spawnpoint.
  maybe<comp::inventory> inventory;      ///< Optional inventory.
  maybe<comp::portal> portal;            ///< Optional portal.
  maybe<comp::point_light> light;        ///< Optional light.
  maybe<int> inventoryRef;  ///< Optional inventory ID, used by inv. triggers.
};

struct tile_object final
{
  tile_id tile{0};             ///< The ID of the associated tile.
  depth_drawable drawable;     ///< Drawable component for the tile object.
  maybe<comp::hitbox> hitbox;  ///< Optional hitbox.
};

struct level final
{
  int id;             ///< Unique ID associated with the level.
  int humanoidLayer;  ///< Layer index where humanoids are rendered.
  int nRows;          ///< The number of rows in the levels.
  int nCols;          ///< The number of columns in the levels.
  int tileWidth;      ///< Width of a tile in the tilemap.
  int tileHeight;     ///< Height of a tile in the tilemap.
  float xRatio;
  float yRatio;
  cen::farea size;                             ///< The size of the level, in pixels.
  float2 playerSpawnPoint;                     ///< The initial position of the player.
  std::vector<ir::tileset> tilesets;           ///< Tilesets used by the level.
  std::vector<comp::tile_layer> groundLayers;  ///< List of "ground" layers.
  std::vector<tile_object> tileObjects;        ///< List of tile objects.
  std::vector<object> objects;                 ///< List of ordinary objects.
};

struct world final
{
  level base;                 ///< Base level that represents the "world".
  std::vector<level> levels;  ///< Dungeons, houses, etc. in the world.
};

}  // namespace wanderer::ir
