#pragma once

#include <centurion.hpp>  // irect, frect
#include <map>            // map
#include <string>         // string
#include <vector>         // vector

#include "components/bed_trigger.hpp"
#include "components/container_trigger.hpp"
#include "components/depth_drawable.hpp"
#include "components/hitbox.hpp"
#include "components/inventory.hpp"
#include "components/object.hpp"
#include "components/plant.hpp"
#include "components/point_light.hpp"
#include "components/portal.hpp"
#include "components/spawnpoint.hpp"
#include "components/tile_animation.hpp"
#include "components/tile_layer.hpp"
#include "components/tile_object.hpp"
#include "core/aliases/depth.hpp"
#include "core/aliases/maybe.hpp"
#include "core/aliases/texture_id.hpp"
#include "core/aliases/tile_id.hpp"

namespace wanderer::ir {

inline constexpr depth_t default_depth{5};

struct texture final
{
  texture_id id;
  std::string path;  // String because it's easier to serialize
};

struct fancy_tile final
{
  depth_t depth = default_depth;          ///< Render depth index.
  maybe<comp::hitbox> hitbox;             ///< Optional hitbox "template".
  maybe<comp::tile_animation> animation;  ///< Optional tile animation.
};

struct tile final
{
  tile_id id{};             ///< Unique ID.
  texture_id texture;       ///< ID of the associated texture.
  cen::irect source;        ///< Source rectangle in the tileset texture.
  maybe<fancy_tile> fancy;  ///< Optional fancy features.
};

struct tileset final
{
  std::string name;
  texture sheet;
  std::map<tile_id, tile> tiles;  ///< Tiles in the tileset.
  float x_ratio{};                ///< Logical tile width divided by tileset tile width.
  float y_ratio{};                ///< Logical tile height divided by tileset tile height.
  int tile_width{};
  int tile_height{};
};

struct depth_drawable final
{
  texture_id texture;
  cen::irect src;
  cen::frect dst;
  int layer{};
  depth_t depth = default_depth;
  float center_y{};
};

struct object final
{
  int id{};                              ///< Unique object ID.
  maybe<comp::hitbox> hitbox;            ///< Optional hitbox.
  maybe<depth_drawable> drawable;        ///< Optional drawable.
  maybe<comp::spawnpoint> spawnpoint;    ///< Optional spawnpoint.
  maybe<comp::inventory> inventory;      ///< Optional inventory.
  maybe<comp::portal> portal;            ///< Optional portal.
  maybe<comp::point_light> light;        ///< Optional light.
  maybe<comp::bed_trigger> bed_trigger;  ///< Optional bed trigger.
  maybe<comp::plant> plant;              ///< Optional plant.
  maybe<int> inventory_ref;  ///< Optional inventory ID, used by inv. triggers.
};

struct tile_object final
{
  tile_id tile{};              ///< The ID of the associated tile.
  depth_drawable drawable;     ///< Drawable component for the tile object.
  maybe<comp::hitbox> hitbox;  ///< Optional hitbox.
};

struct level final
{
  int id{};                   ///< Unique ID associated with the level.
  int humanoid_layer{};       ///< Layer index where humanoids are rendered.
  int row_count{};            ///< The number of rows in the levels.
  int col_count{};            ///< The number of columns in the levels.
  int tile_width{};           ///< Width of a tile in the tilemap.
  int tile_height{};          ///< Height of a tile in the tilemap.
  float x_ratio{};            ///< Logical tile width divided by tileset tile width.
  float y_ratio{};            ///< Logical tile height divided by tileset tile height.
  cen::farea size;            ///< The size of the level, in pixels.
  float2 player_spawn_point;  ///< The initial position of the player.
  std::vector<ir::tileset> tilesets;            ///< Tilesets used by the level.
  std::vector<comp::tile_layer> ground_layers;  ///< List of "ground" layers.
  std::vector<tile_object> tile_objects;        ///< List of tile objects.
  std::vector<object> objects;                  ///< List of ordinary objects.
};

struct world final
{
  level base;                 ///< Base level that represents the "world".
  std::vector<level> levels;  ///< Dungeons, houses, etc. in the world.
};

}  // namespace wanderer::ir
