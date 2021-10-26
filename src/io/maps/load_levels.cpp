#include "load_levels.hpp"

#include <filesystem>   // path
#include <string_view>  // string_view_literals
#include <vector>       // vector

#include <rune/everything.hpp>
#include <tactile-io/parser.hpp>

#include "components/ai/humanoid.hpp"
#include "components/associated_entity.hpp"
#include "components/associated_object.hpp"
#include "components/ctx/level_size.hpp"
#include "components/ctx/viewport.hpp"
#include "components/gfx/drawable.hpp"
#include "components/gfx/point_light.hpp"
#include "components/gfx/tile_animation.hpp"
#include "components/items/inventory.hpp"
#include "components/lvl/level.hpp"
#include "components/lvl/portal.hpp"
#include "components/lvl/spawnpoint.hpp"
#include "components/object.hpp"
#include "components/plant.hpp"
#include "components/tiles/tile.hpp"
#include "components/tiles/tile_layer.hpp"
#include "components/tiles/tile_object.hpp"
#include "components/tiles/tilemap.hpp"
#include "components/tiles/tileset.hpp"
#include "components/trigger.hpp"
#include "core/ecs/make_registry.hpp"
#include "core/ecs/registry_utils.hpp"
#include "core/resources.hpp"
#include "core/utils/centurion_utils.hpp"
#include "profile.hpp"
#include "systems/ai/humanoid/humanoid_factory_system.hpp"
#include "systems/gfx/depth_system.hpp"
#include "systems/gfx/drawable_system.hpp"
#include "systems/gfx/viewport_system.hpp"
#include "systems/physics/hitbox_system.hpp"
#include "tactile_io_utils.hpp"
#include "wanderer_std.hpp"

namespace wanderer {
namespace {

// TODO handle x- and y-ratios on a tileset-per-tileset basis

[[nodiscard]] auto GetTextureId(const Tactile::IO::Tileset& irTileset) -> rune::texture_id
{
  const auto id = 1'000 + GetInt(irTileset, "id"); /* Offset ID to avoid clashes */
  return rune::texture_id(id);
}

void LoadTilesetTextures(const Tactile::IO::Map& irMap, GraphicsContext& graphics)
{
  WANDERER_PROFILE_START

  Tactile::IO::EachTileset(irMap, [&](const Tactile::IO::Tileset& irTileset) {
    graphics.load(GetTextureId(irTileset),
                  std::filesystem::path{Tactile::IO::GetImagePath(irTileset)}.string());
  });

  WANDERER_PROFILE_END("Loaded tileset textures")
}

void CreateTiles(const Tactile::IO::Tileset& irTileset,
                 entt::registry& registry,
                 comp::Tileset& tileset,
                 const rune::texture_index texture)
{
  const auto first = Tactile::IO::GetFirstGlobalId(irTileset);

  const auto count = Tactile::IO::GetTileCount(irTileset);
  const auto columns = Tactile::IO::GetColumnCount(irTileset);

  const auto tileWidth = Tactile::IO::GetTileWidth(irTileset);
  const auto tileHeight = Tactile::IO::GetTileHeight(irTileset);

  int32 id = first;
  for (int32 index = 0; index < count; ++index, ++id) {
    const auto tileEntity = registry.create();
    auto& tile = registry.emplace<comp::Tile>(tileEntity);
    tile.id = TileID(id);
    tile.texture = texture;
    tile.depth = 5;

    const auto [row, col] = rune::index_to_matrix(index, columns);
    tile.src.set_x(col * tileWidth);
    tile.src.set_y(row * tileHeight);
    tile.src.set_width(tileWidth);
    tile.src.set_height(tileHeight);

    tileset.tiles[tile.id] = tileEntity;
  }
}

void AddAnimation(const Tactile::IO::Tile& irTile,
                  entt::registry& registry,
                  const entt::entity tileEntity,
                  const int32 firstId)
{
  auto& animation = registry.emplace<comp::TileAnimation>(tileEntity);
  animation.index = 0;
  animation.then = cen::counter::ticks();

  Tactile::IO::EachAnimationFrame(
      irTile,
      [&](const Tactile::IO::AnimationFrame& irFrame) {
        auto& frame = animation.frames.emplace_back();
        frame.tile = TileID(firstId) + TileID(Tactile::IO::GetTile(irFrame));
        frame.duration = ms_t{Tactile::IO::GetDuration(irFrame)};
      });
}

void AddHitbox(const Tactile::IO::Object& irObject,
               entt::registry& registry,
               const entt::entity tileEntity,
               const float xRatio,
               const float yRatio)
{
  const float2 offset{Tactile::IO::GetX(irObject) * xRatio,
                      Tactile::IO::GetY(irObject) * yRatio};
  const cen::farea size{Tactile::IO::GetWidth(irObject) * xRatio,
                        Tactile::IO::GetHeight(irObject) * yRatio};

  registry.emplace<comp::Hitbox>(tileEntity, sys::MakeHitbox({{offset, size}}));
}

void AddTileMetaInfo(const Tactile::IO::Tileset& irTileset,
                     entt::registry& registry,
                     comp::Tileset& tileset,
                     const int32 firstId)
{
  const auto tileWidth = Tactile::IO::GetTileWidth(irTileset);
  const auto tileHeight = Tactile::IO::GetTileHeight(irTileset);

  const auto xRatio = glob::tile_width<float> / static_cast<float>(tileWidth);
  const auto yRatio = glob::tile_height<float> / static_cast<float>(tileHeight);

  Tactile::IO::EachTileInfo(irTileset, [&](const Tactile::IO::Tile& irTile) {
    const auto id = firstId + Tactile::IO::GetId(irTile);
    const auto tileEntity = tileset.tiles.at(TileID(id));

    registry.get<comp::Tile>(tileEntity).depth = GetInt(irTile, "depth", 5);

    if (Tactile::IO::GetAnimationFrameCount(irTile) != 0) {
      AddAnimation(irTile, registry, tileEntity, firstId);
    }

    Tactile::IO::EachObject(irTile, [&](const Tactile::IO::Object& irObject) {
      const auto* tag = Tactile::IO::GetTag(irObject);

      using namespace std::string_view_literals;
      if (tag == "Hitbox"sv) {
        AddHitbox(irObject, registry, tileEntity, xRatio, yRatio);
      }
    });
  });
}

void CreateTileset(const Tactile::IO::Map& irMap,
                   GraphicsContext& graphics,
                   entt::registry& registry,
                   const entt::entity tilesetEntity)
{
  auto& tileset = registry.emplace<comp::Tileset>(tilesetEntity);

  Tactile::IO::EachTileset(irMap, [&](const Tactile::IO::Tileset& irTileset) {
    const auto texture = graphics.to_index(GetTextureId(irTileset));
    const auto first = Tactile::IO::GetFirstGlobalId(irTileset);

    CreateTiles(irTileset, registry, tileset, texture);
    AddTileMetaInfo(irTileset, registry, tileset, first);
  });
}

[[nodiscard]] auto MakeTileMatrix(const int32 nRows, const int32 nCols)
    -> std::vector<std::vector<TileID>>
{
  return {static_cast<usize>(nRows),
          std::vector<TileID>(static_cast<usize>(nCols), glob::empty_tile)};
}

void AddGroundLayer(const Tactile::IO::TileLayer& irTileLayer,
                    comp::Level& level,
                    const int32 layerIndex)
{
  const auto entity = level.registry.create();
  auto& layer = level.registry.emplace<comp::TileLayer>(entity);
  layer.z = layerIndex;

  const auto nRows = Tactile::IO::GetRowCount(irTileLayer);
  const auto nCols = Tactile::IO::GetColumnCount(irTileLayer);
  layer.matrix = MakeTileMatrix(nRows, nCols);

  for (int32 row = 0; row < nRows; ++row) {
    for (int32 col = 0; col < nCols; ++col) {
      layer.matrix[row][col] = TileID(Tactile::IO::GetTile(irTileLayer, row, col));
    }
  }

  level.registry.sort<comp::TileLayer>(
      [](const comp::TileLayer& lhs, const comp::TileLayer& rhs) noexcept {
        return lhs.z < rhs.z;
      });
}

void InsertHitbox(aabb_tree& tree, const entt::entity entity, const comp::Hitbox& hitbox)
{
  const auto lower = to_rune_vector(hitbox.bounds.position());
  const auto upper = lower + to_rune_vector(hitbox.bounds.size());
  tree.insert(entity, lower, upper);
}

void AddTileObject(comp::Level& level,
                   const TileID id,
                   const float x,
                   const float y,
                   const int32 layerIndex)
{
  auto& registry = level.registry;
  const auto& tileset = registry.get<comp::Tileset>(level.tileset);

  const auto tileEntity = tileset.tiles.at(id);
  const auto& tile = registry.get<comp::Tile>(tileEntity);

  const auto entity = registry.create();
  auto& tileObject = registry.emplace<comp::TileObject>(entity);
  tileObject.tile_entity = tileEntity;

  auto& drawable = registry.emplace<comp::Drawable>(entity);
  drawable.texture = tile.texture;
  drawable.src = tile.src;
  drawable.dst = cen::frect{{x, y}, glob::tile_size<cen::farea>};
  drawable.depth = tile.depth;
  drawable.layer = layerIndex;

  if (const auto* tileHitbox = registry.try_get<comp::Hitbox>(tileEntity)) {
    const auto& hitbox =
        registry.emplace<comp::Hitbox>(entity, sys::WithPosition(*tileHitbox, {x, y}));
    InsertHitbox(level.tree, entity, hitbox);
  }

  if (const auto* tileAnimation = registry.try_get<comp::TileAnimation>(tileEntity)) {
    registry.emplace<comp::TileAnimation>(entity, *tileAnimation);
  }
}

void AddTileObjects(const Tactile::IO::Map& irMap,
                    const Tactile::IO::TileLayer& irTileLayer,
                    comp::Level& level,
                    const int32 layerIndex)
{
  const auto fTileWidth = static_cast<float>(Tactile::IO::GetTileWidth(irMap));
  const auto fTileHeight = static_cast<float>(Tactile::IO::GetTileHeight(irMap));

  const auto xRatio = glob::tile_width<float> / fTileWidth;
  const auto yRatio = glob::tile_height<float> / fTileHeight;

  const auto tw = fTileWidth * xRatio;
  const auto th = fTileHeight * yRatio;

  const auto nRows = Tactile::IO::GetRowCount(irTileLayer);
  const auto nCols = Tactile::IO::GetColumnCount(irTileLayer);

  for (int32 row = 0; row < nRows; ++row) {
    for (int32 col = 0; col < nCols; ++col) {
      const auto id = TileID(Tactile::IO::GetTile(irTileLayer, row, col));
      if (!is_empty(id)) {
        AddTileObject(level,
                      id,
                      static_cast<float>(col) * tw,
                      static_cast<float>(row) * th,
                      layerIndex);
      }
    }
  }
}

void LoadTileLayer(const Tactile::IO::Map& irMap,
                   const Tactile::IO::Layer& irLayer,
                   comp::Level& level,
                   const int32 layerIndex)
{
  const auto& irTileLayer = Tactile::IO::GetTileLayer(irLayer);
  if (GetBool(irLayer, "ground")) {
    AddGroundLayer(irTileLayer, level, layerIndex);
  }
  else {
    AddTileObjects(irMap, irTileLayer, level, layerIndex);
  }
}

void LoadSpawnpoint(const Tactile::IO::Object& irObject,
                    comp::Level& level,
                    const entt::entity entity,
                    const float xRatio,
                    const float yRatio)
{
  auto& spawnpoint = level.registry.emplace<comp::Spawnpoint>(entity);
  spawnpoint.position =
      float2{Tactile::IO::GetX(irObject) * xRatio, Tactile::IO::GetY(irObject) * yRatio};

  // TODO only do this for humanoids, when animals are added
  spawnpoint.position.x -= glob::humanoid_draw_width / 2.0f;
  spawnpoint.position.y -= glob::humanoid_draw_height / 2.0f;

  const auto* type = GetString(irObject, "entity");

  using namespace std::string_view_literals;
  if (type == "player"sv) {
    spawnpoint.type = comp::SpawnpointType::player;
    level.player_spawn_position = spawnpoint.position;
  }
  else if (type == "skeleton"sv) {
    spawnpoint.type = comp::SpawnpointType::skeleton;
  }
  else {
    throw WandererError{"Did not recognize spawnpoint type!"};
  }
}

void LoadInventory(const Tactile::IO::Object& irObject,
                   comp::Level& level,
                   const entt::entity entity)
{
  auto& inventory = level.registry.emplace<comp::Inventory>(entity);

  inventory.capacity = GetInt(irObject, "capacity");
  inventory.items.reserve(inventory.capacity);

  if (GetBool(irObject, "hasRandomLoot")) {
    // TODO
  }
}

void LoadHitbox(const Tactile::IO::Object& irObject,
                comp::Level& level,
                const entt::entity entity,
                const float xRatio,
                const float yRatio)
{
  auto& registry = level.registry;

  const float2 position{Tactile::IO::GetX(irObject) * xRatio,
                        Tactile::IO::GetY(irObject) * yRatio};
  const cen::farea size{Tactile::IO::GetWidth(irObject) * xRatio,
                        Tactile::IO::GetHeight(irObject) * yRatio};

  /* We use no offset for object hitboxes */
  auto& hitbox = registry.emplace<comp::Hitbox>(entity, sys::MakeHitbox({{{}, size}}));
  hitbox.enabled = false;

  sys::SetPosition(hitbox, position);
  InsertHitbox(level.tree, entity, hitbox);
}

void LoadContainerTrigger(const Tactile::IO::Object& irObject,
                          comp::Level& level,
                          const entt::entity entity,
                          const float xRatio,
                          const float yRatio)
{
  level.registry.emplace<comp::Trigger>(entity, comp::TriggerType::container);

  const auto id = GetObject(irObject, "container");
  level.registry.emplace<comp::AssociatedObject>(entity, id);

  LoadHitbox(irObject, level, entity, xRatio, yRatio);
}

void LoadBedTrigger(const Tactile::IO::Object& irObject,
                    comp::Level& level,
                    const entt::entity entity,
                    const float xRatio,
                    const float yRatio)
{
  level.registry.emplace<comp::Trigger>(entity, comp::TriggerType::bed);
  LoadHitbox(irObject, level, entity, xRatio, yRatio);
}

void LoadPortal(const Tactile::IO::Object& irObject,
                comp::Level& level,
                const entt::entity entity,
                const float xRatio,
                const float yRatio)
{
  level.registry.emplace<comp::Trigger>(entity, comp::TriggerType::portal);

  auto& portal = level.registry.emplace<comp::Portal>(entity);
  portal.path = GetFile(irObject, "path");
  portal.target = MapID{GetInt(irObject, "target")};

  LoadHitbox(irObject, level, entity, xRatio, yRatio);
}

void LoadLight(const Tactile::IO::Object& irObject,
               comp::Level& level,
               const entt::entity entity,
               const float xRatio,
               const float yRatio)
{
  auto& light = level.registry.emplace<comp::PointLight>(entity);
  light.size = Tactile::IO::GetWidth(irObject) * xRatio;

  const auto x = Tactile::IO::GetX(irObject) * xRatio;
  const auto y = Tactile::IO::GetY(irObject) * yRatio;

  light.position.x = x + (light.size / 2.0f);
  light.position.y = y + (light.size / 2.0f);

  light.fluctuation_limit = 5;
  light.fluctuation_step = 1;
  light.fluctuation = 0;

  light.fluctuation_limit = GetFloat(irObject, "fluctuationLimit", 5.0f);
  light.fluctuation_step = GetFloat(irObject, "fluctuationStep", 1.0f);
}

void LoadPlant(const Tactile::IO::Object& irObject,
               comp::Level& level,
               const entt::entity entity,
               const float xRatio,
               const float yRatio)
{
  //  auto& plant = level.registry.emplace<comp::Plant>(entity);
  //  plant.rate = GetFloat(irObject, "rate");

  //  const auto* tileset = GetString(irObject, "tileset");
  //  const auto offset = get_tileset_offset(data, tileset);
  //  const auto tileSize = get_tileset_tile_size(data, tileset);

  //  plant.tile_height = tileSize->height;
  //  plant.tiles = parse_tiles(rune::tmx::get_string(object.properties, "tiles"),
  //  offset);
  //
  //  if (const auto* tallTiles = rune::tmx::get_if_string(object.properties,
  //  "tallTiles")) {
  //    plant.tall = parse_tiles(*tallTiles, offset);
  //  }

  // objectData.drawable = make_depth_drawable(tile, pos, size, data.humanoid_layer);
}

[[nodiscard]] auto FindObject(const entt::registry& registry, const int32 id)
    -> entt::entity
{
  for (auto&& [entity, object] : registry.view<comp::Object>().each()) {
    if (object.id == id) {
      return entity;
    }
  }

  return entt::null;
}

void LoadObjectLayer(const Tactile::IO::Map& irMap,
                     const Tactile::IO::Layer& irLayer,
                     comp::Level& level,
                     const float xRatio,
                     const float yRatio)
{
  const auto& irObjectLayer = Tactile::IO::GetObjectLayer(irLayer);

  Tactile::IO::EachObject(irObjectLayer, [&](const Tactile::IO::Object& irObject) {
    const auto entity = level.registry.create();

    auto& object = level.registry.emplace<comp::Object>(entity);
    object.id = Tactile::IO::GetId(irObject);

    const auto* tag = Tactile::IO::GetTag(irObject);

    using namespace std::string_view_literals;
    if (tag == "Spawnpoint"sv) {
      LoadSpawnpoint(irObject, level, entity, xRatio, yRatio);
    }
    else if (tag == "Container"sv) {
      LoadInventory(irObject, level, entity);
    }
    else if (tag == "ContainerTrigger"sv) {
      LoadContainerTrigger(irObject, level, entity, xRatio, yRatio);
    }
    else if (tag == "BedTrigger"sv) {
      LoadBedTrigger(irObject, level, entity, xRatio, yRatio);
    }
    else if (tag == "Portal"sv) {
      LoadPortal(irObject, level, entity, xRatio, yRatio);
    }
    else if (tag == "Light"sv) {
      LoadLight(irObject, level, entity, xRatio, yRatio);
    }
    else if (tag == "Plant"sv) {
      LoadPlant(irObject, level, entity, xRatio, yRatio);
    }
  });

  for (auto&& [entity, associatedObject] :
       level.registry.view<comp::AssociatedObject>().each())
  {
    auto& association = level.registry.emplace<comp::AssociatedEntity>(entity);
    association.entity = FindObject(level.registry, associatedObject.object_id);
  }
}

void CreateLayers(const Tactile::IO::Map& irMap, comp::Level& level)
{
  /* We parse tile layers and objects layers separately in order to guarantee that the
     tile data is available once the objects are parsed, since that makes our lives a
     little easier. */

  const auto xRatio = 2.0f;  // FIXME
  const auto yRatio = 2.0f;  // FIXME

  Tactile::IO::EachLayer(irMap,
                         [&, index = 0](const Tactile::IO::Layer& irLayer) mutable {
                           if (Tactile::IO::IsTileLayer(irLayer)) {
                             LoadTileLayer(irMap, irLayer, level, index);
                             ++index;
                           }
                         });

  Tactile::IO::EachLayer(irMap, [&](const Tactile::IO::Layer& irLayer) {
    if (Tactile::IO::IsObjectLayer(irLayer)) {
      LoadObjectLayer(irMap, irLayer, level, xRatio, yRatio);
    }
  });
}

void CreateHumanoids(const Tactile::IO::Map& irMap,
                     comp::Level& level,
                     GraphicsContext& graphics)
{
  /* The player has to be created before other humanoids! */
  sys::MakePlayer(level, graphics);

  for (auto&& [entity, spawnpoint] : level.registry.view<comp::Spawnpoint>().each()) {
    switch (spawnpoint.type) {
      case comp::SpawnpointType::player:
        break;

      case comp::SpawnpointType::skeleton: {
        sys::MakeSkeleton(level, spawnpoint.position, graphics);
        break;
      }
    }
  }

  const auto& tilemap = level.registry.get<comp::Tilemap>(level.tilemap);
  for (auto&& [entity, drawable] :
       level.registry.view<comp::Drawable, comp::Humanoid>().each())
  {
    drawable.layer = tilemap.humanoid_layer;
  }
}

auto LoadLevel(entt::registry& shared,
               GraphicsContext& graphics,
               const std::filesystem::path& path) -> entt::entity
{
  WANDERER_PROFILE_START

  if (const auto irMap = Tactile::IO::ParseMap(path)) {
    const auto id = MapID(GetInt(*irMap, "id"));

    for (auto&& [entity, level] : shared.view<comp::Level>().each()) {
      if (level.id == id) {
        return entity;
      }
    }

    CENTURION_LOG_DEBUG("Loading level %s", path.string().c_str());

    LoadTilesetTextures(*irMap, graphics);

    const auto levelEntity = shared.create();
    auto& level = shared.emplace<comp::Level>(levelEntity);
    level.id = id;

    level.registry = MakeRegistry();
    level.tree.disable_thickness_factor();

    level.tilemap = level.registry.create();
    level.tileset = level.registry.create();

    auto& tilemap = level.registry.emplace<comp::Tilemap>(level.tilemap);
    tilemap.id = MapID{level.id};
    tilemap.row_count = Tactile::IO::GetRowCount(*irMap);
    tilemap.col_count = Tactile::IO::GetColumnCount(*irMap);
    tilemap.size = {static_cast<float>(tilemap.col_count) * glob::tile_width<float>,
                    static_cast<float>(tilemap.row_count) * glob::tile_height<float>};
    tilemap.humanoid_layer = GetInt(*irMap, "humanoidLayer");

    auto& size = level.registry.set<ctx::LevelSize>();
    size.row_count = tilemap.row_count;
    size.col_count = tilemap.col_count;

    level.registry.set<ctx::Viewport>(sys::MakeViewport(tilemap.size));

    CreateTileset(*irMap, graphics, level.registry, level.tileset);
    CreateLayers(*irMap, level);
    CreateHumanoids(*irMap, level, graphics);

    sys::CenterViewportOn(level.registry, level.player_spawn_position.value());
    sys::UpdateDrawables(level.registry);
    sys::UpdateDepth(level.registry, sys::SortStrategy::StdSort);

    if constexpr (cen::is_release_build()) {
      /* This is very slow in debug builds, so we avoid it */
      level.tree.rebuild();
    }

    WANDERER_PROFILE_END("Loaded level")

    for (auto&& [entity, portal] : level.registry.view<comp::Portal>().each()) {
      if (!portal.path.empty() && portal.path != ".") {
        LoadLevel(shared, graphics, path.parent_path() / portal.path);
      }
    }

    return levelEntity;
  }
  else {
    throw WandererError{"Failed to parse map!"};
  }
}

}  // namespace

void LoadLevels(entt::registry& shared, GraphicsContext& graphics)
{
  const auto path = std::filesystem::absolute(resources::map("main.json"));
  const auto root = LoadLevel(shared, graphics, path);
  shared.emplace<comp::ActiveLevel>(root);

  auto& rootLevel = shared.get<comp::Level>(root);
  rootLevel.registry.ctx<ctx::Viewport>().keep_in_bounds = true;
}

}  // namespace wanderer
