#pragma once

#include <map>     // map
#include <string>  // string
#include <vector>  // vector

#include <centurion.hpp>  // irect, frect

#include "common/ints.hpp"
#include "common/maybe.hpp"
#include "common/texture_id.hpp"
#include "common/tile_id.hpp"
#include "components/associated_entity.hpp"
#include "components/gfx/drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/portal.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/object.hpp"
#include "components/physics/hitbox.hpp"
#include "components/plant.hpp"
#include "components/tiles/tile_layer.hpp"
#include "components/tiles/tile_object.hpp"
#include "components/trigger.hpp"

namespace wanderer::ir {

inline constexpr int32 default_depth = 5;

struct texture final
{
  texture_id id;
  std::string path;  // String because it's easier to serialize
};

struct fancy_tile final
{
  int32 depth = default_depth;           ///< Render depth index.
  maybe<comp::Hitbox> hitbox;            ///< Optional hitbox "template".
  maybe<comp::TileAnimation> animation;  ///< Optional tile animation.
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
  int32 tile_width{};
  int32 tile_height{};
};

struct drawable final
{
  texture_id texture;
  cen::irect src;
  cen::frect dst;
  int32 layer{};
  int32 depth = default_depth;
  float center_y{};
};

struct object final
{
  int32 id{};                          ///< Unique object ID.
  maybe<comp::Hitbox> hitbox;          ///< Optional hitbox.
  maybe<drawable> drawable;            ///< Optional drawable.
  maybe<comp::Spawnpoint> spawnpoint;  ///< Optional spawnpoint.
  maybe<comp::Inventory> inventory;    ///< Optional inventory.
  maybe<comp::Portal> portal;          ///< Optional portal.
  maybe<comp::PointLight> light;       ///< Optional light.
  maybe<comp::Plant> plant;            ///< Optional plant.
  maybe<comp::TriggerType> trigger_type;
  maybe<int32> object_ref;  ///< Optional associated object ID, used by inv. triggers.
};

struct tile_object final
{
  tile_id tile{};              ///< The ID of the associated tile.
  drawable drawable;           ///< Drawable component for the tile object.
  maybe<comp::Hitbox> hitbox;  ///< Optional hitbox.
};

struct level final
{
  int32 id{};                 ///< Unique ID associated with the level.
  int32 humanoid_layer{};     ///< Layer index where humanoids are rendered.
  int32 row_count{};          ///< The number of rows in the levels.
  int32 col_count{};          ///< The number of columns in the levels.
  int32 tile_width{};         ///< Width of a tile in the tilemap.
  int32 tile_height{};        ///< Height of a tile in the tilemap.
  float x_ratio{};            ///< Logical tile width divided by tileset tile width.
  float y_ratio{};            ///< Logical tile height divided by tileset tile height.
  cen::farea size;            ///< The size of the level, in pixels.
  float2 player_spawn_point;  ///< The initial position of the player.
  std::vector<ir::tileset> tilesets;           ///< Tilesets used by the level.
  std::vector<comp::TileLayer> ground_layers;  ///< List of "ground" layers.
  std::vector<tile_object> tile_objects;       ///< List of tile objects.
  std::vector<object> objects;                 ///< List of ordinary objects.
};

struct world final
{
  level base;                 ///< Base level that represents the "world".
  std::vector<level> levels;  ///< Dungeons, houses, etc. in the world.
};

}  // namespace wanderer::ir
