#include "create_object_layer.hpp"

#include <sstream>      // stringstream
#include <string>       // string, getline
#include <string_view>  // string_view, sv
#include <utility>      // move
#include <vector>       // vector

#include "components/associated_entity.hpp"
#include "components/associated_object.hpp"
#include "components/drawable.hpp"
#include "components/hitbox.hpp"
#include "components/inventory.hpp"
#include "components/object.hpp"
#include "components/plant.hpp"
#include "components/point_light.hpp"
#include "components/portal.hpp"
#include "components/spawnpoint.hpp"
#include "components/tilemap.hpp"
#include "components/trigger.hpp"
#include "create_tileset.hpp"
#include "hitboxes.hpp"
#include "systems/physics/hitbox_system.hpp"
#include "systems/tile_system.hpp"
#include "tactile_io_utils.hpp"

namespace wanderer {
namespace {

void AddHitbox(const Tactile::IO::Object& irObject,
               entt::registry& registry,
               const entt::entity entity,
               const float xRatio,
               const float yRatio)
{
  const float2 position{Tactile::IO::GetX(irObject) * xRatio,
                        Tactile::IO::GetY(irObject) * yRatio};
  const cen::farea size{Tactile::IO::GetWidth(irObject) * xRatio,
                        Tactile::IO::GetHeight(irObject) * yRatio};

  /* We use no offset for object hitboxes */
  auto& hitbox = registry.emplace<Hitbox>(entity, sys::MakeHitbox({{{}, size}}));

  sys::SetPosition(hitbox, position);
}

void LoadSpawnpoint(const Tactile::IO::Object& irObject,
                    Level& level,
                    const entt::entity entity,
                    const float2 ratio)
{
  auto& spawnpoint = level.registry.emplace<Spawnpoint>(entity);
  spawnpoint.position = float2{Tactile::IO::GetX(irObject) * ratio.x,
                               Tactile::IO::GetY(irObject) * ratio.y};

  // TODO only do this for humanoids, when animals are added
  spawnpoint.position.x -= glob::humanoid_draw_width / 2.0f;
  spawnpoint.position.y -= glob::humanoid_draw_height / 2.0f;

  const auto* type = GetString(irObject, "entity");

  using namespace std::string_view_literals;
  if (type == "player"sv) {
    spawnpoint.type = SpawnpointType::player;
    level.player_spawn_position = spawnpoint.position;
  }
  else if (type == "skeleton"sv) {
    spawnpoint.type = SpawnpointType::skeleton;
  }
  else {
    throw WandererError{"Did not recognize spawnpoint type!"};
  }
}

void LoadInventory(const Tactile::IO::Object& irObject,
                   Level& level,
                   const entt::entity entity)
{
  auto& inventory = level.registry.emplace<Inventory>(entity);

  inventory.capacity = GetInt(irObject, "capacity");
  inventory.items.reserve(inventory.capacity);

  if (GetBool(irObject, "hasRandomLoot")) {
    // TODO
  }
}

void LoadContainerTrigger(const Tactile::IO::Object& irObject,
                          Level& level,
                          const entt::entity entity,
                          const float2 ratio)
{
  level.registry.emplace<Trigger>(entity, TriggerType::container);

  const auto id = GetObject(irObject, "container");
  level.registry.emplace<AssociatedObject>(entity, id);

  AddHitbox(irObject, level.registry, entity, ratio.x, ratio.y);
}

void LoadBedTrigger(const Tactile::IO::Object& irObject,
                    Level& level,
                    const entt::entity entity,
                    const float2 ratio)
{
  level.registry.emplace<Trigger>(entity, TriggerType::bed);
  AddHitbox(irObject, level.registry, entity, ratio.x, ratio.y);
}

void LoadPortal(const Tactile::IO::Object& irObject,
                Level& level,
                const entt::entity entity,
                const float2 ratio)
{
  level.registry.emplace<Trigger>(entity, TriggerType::portal);

  auto& portal = level.registry.emplace<Portal>(entity);
  portal.path = GetFile(irObject, "path");
  portal.target = MapID{GetInt(irObject, "target")};

  AddHitbox(irObject, level.registry, entity, ratio.x, ratio.y);
}

void LoadLight(const Tactile::IO::Object& irObject,
               Level& level,
               const entt::entity entity,
               const float2 ratio)
{
  auto& light = level.registry.emplace<PointLight>(entity);
  light.size = Tactile::IO::GetWidth(irObject) * ratio.x;

  const auto x = Tactile::IO::GetX(irObject) * ratio.x;
  const auto y = Tactile::IO::GetY(irObject) * ratio.y;

  light.position.x = x + (light.size / 2.0f);
  light.position.y = y + (light.size / 2.0f);

  light.fluctuation_limit = 5;
  light.fluctuation_step = 1;
  light.fluctuation = 0;

  light.fluctuation_limit = GetFloat(irObject, "fluctuationLimit", 5.0f);
  light.fluctuation_step = GetFloat(irObject, "fluctuationStep", 1.0f);
}

[[nodiscard]] auto GetTileset(const Tactile::IO::Map& irMap,
                              const std::string_view tilesetName)
    -> const Tactile::IO::Tileset&
{
  const auto count = Tactile::IO::GetTilesetCount(irMap);
  for (usize index = 0; index < count; ++index) {
    const auto& irTileset = Tactile::IO::GetTileset(irMap, index);
    if (tilesetName == Tactile::IO::GetName(irTileset)) {
      return irTileset;
    }
  }

  throw WandererError{"Did not find tileset with the specified name!"};
}

[[nodiscard]] auto GetTilesetOffset(const Tactile::IO::Map& irMap,
                                    const std::string_view tilesetName) -> int32
{
  int32 offset = 0;

  const auto count = Tactile::IO::GetTilesetCount(irMap);
  for (usize index = 0; index < count; ++index) {
    const auto& irTileset = Tactile::IO::GetTileset(irMap, index);
    if (tilesetName == Tactile::IO::GetName(irTileset)) {
      break;
    }
    else {
      offset += Tactile::IO::GetTileCount(irTileset) + 1;
    }
  }

  return offset;
}

// TODO move
[[nodiscard]] auto ParseCSV(const std::string& csv) -> std::vector<std::string>
{
  std::vector<std::string> tokens;

  std::stringstream stream{csv};
  std::string token;

  while (std::getline(stream, token, ',')) {
    tokens.push_back(std::move(token));
    token.clear();
  }

  return tokens;
}

[[nodiscard]] auto ParseTileCSV(const std::string& csv, const int32 offset)
    -> std::vector<TileID>
{
  const auto tokens = ParseCSV(csv);

  std::vector<TileID> tiles;
  tiles.reserve(tokens.size());

  for (const auto& token : tokens) {
    const TileID tile{offset + rune::from_string<TileID::value_type>(token).value()};
    tiles.push_back(tile);
  }

  return tiles;
}

void LoadPlant(const Tactile::IO::Map& irMap,
               const Tactile::IO::Object& irObject,
               Level& level,
               GraphicsContext& graphics,
               const entt::entity entity,
               const float2 ratio)
{
  auto& registry = level.registry;

  auto& plant = registry.emplace<Plant>(entity);
  plant.rate = GetFloat(irObject, "rate");

  const auto* name = GetString(irObject, "tileset");
  const auto& irTileset = GetTileset(irMap, name);
  const auto offset = Tactile::IO::GetFirstGlobalId(irTileset);

  plant.tile_height = Tactile::IO::GetTileHeight(irTileset);
  plant.tiles = ParseTileCSV(GetString(irObject, "tiles"), offset);

  if (HasProperty(irObject, "tallTiles")) {
    plant.tall = ParseTileCSV(GetString(irObject, "tallTiles"), offset);
  }

  const auto x = Tactile::IO::GetX(irObject) * ratio.x;
  const auto y = Tactile::IO::GetY(irObject) * ratio.y;
  const auto width = Tactile::IO::GetWidth(irObject) * ratio.x;
  const auto height = Tactile::IO::GetHeight(irObject) * ratio.y;
  const auto& tilemap = registry.ctx<Tilemap>();

  plant.base_y = y;

  const auto first = plant.tiles.front();
  const auto& tile = sys::GetTile(registry, first);

  auto& drawable = registry.emplace<Drawable>(entity);
  drawable.texture = graphics.ToIndex(GetTextureId(irTileset));
  drawable.dst.set_position({x, y});
  drawable.dst.set_size({width, height});
  drawable.src = tile.src;
  drawable.depth = tile.depth;
  drawable.layer = tilemap.humanoid_layer;
}

[[nodiscard]] auto FindObject(const entt::registry& registry, const int32 id)
    -> entt::entity
{
  for (auto&& [entity, object] : registry.view<Object>().each()) {
    if (object.id == id) {
      return entity;
    }
  }

  return entt::null;
}

void CreateObject(const Tactile::IO::Map& irMap,
                  const Tactile::IO::Object& irObject,
                  Level& level,
                  GraphicsContext& graphics,
                  const float2 ratio)
{
  const auto entity = level.registry.create();

  auto& object = level.registry.emplace<Object>(entity);
  object.id = Tactile::IO::GetId(irObject);

  const auto* tag = Tactile::IO::GetTag(irObject);

  using namespace std::string_view_literals;
  if (tag == "Spawnpoint"sv) {
    LoadSpawnpoint(irObject, level, entity, ratio);
  }
  else if (tag == "Container"sv) {
    LoadInventory(irObject, level, entity);
  }
  else if (tag == "ContainerTrigger"sv) {
    LoadContainerTrigger(irObject, level, entity, ratio);
  }
  else if (tag == "BedTrigger"sv) {
    LoadBedTrigger(irObject, level, entity, ratio);
  }
  else if (tag == "Portal"sv) {
    LoadPortal(irObject, level, entity, ratio);
  }
  else if (tag == "Light"sv) {
    LoadLight(irObject, level, entity, ratio);
  }
  else if (tag == "Plant"sv) {
    LoadPlant(irMap, irObject, level, graphics, entity, ratio);
  }
}

}  // namespace

void CreateObjectLayer(const Tactile::IO::Map& irMap,
                       const Tactile::IO::Layer& irLayer,
                       Level& level,
                       GraphicsContext& graphics,
                       const float2 ratio)
{
  const auto& irObjectLayer = Tactile::IO::GetObjectLayer(irLayer);

  Tactile::IO::EachObject(irObjectLayer, [&](const Tactile::IO::Object& irObject) {
    CreateObject(irMap, irObject, level, graphics, ratio);
  });

  for (auto&& [entity, associatedObject] : level.registry.view<AssociatedObject>().each())
  {
    auto& association = level.registry.emplace<AssociatedEntity>(entity);
    association.entity = FindObject(level.registry, associatedObject.object_id);
  }
}

}  // namespace wanderer
