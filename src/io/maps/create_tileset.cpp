#include "create_tileset.hpp"

#include <filesystem>   // path
#include <string_view>  // sv

#include "components/gfx/tile_animation.hpp"
#include "components/physics/hitbox.hpp"
#include "components/tiles/tileset.hpp"
#include "core/game_constants.hpp"
#include "profile.hpp"
#include "systems/physics/hitbox_system.hpp"
#include "tactile_io_utils.hpp"

namespace wanderer {
namespace {

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
               const float2 ratio)
{
  const float2 offset{Tactile::IO::GetX(irObject) * ratio.x,
                      Tactile::IO::GetY(irObject) * ratio.y};
  const cen::farea size{Tactile::IO::GetWidth(irObject) * ratio.x,
                        Tactile::IO::GetHeight(irObject) * ratio.y};

  registry.emplace<comp::Hitbox>(tileEntity, sys::MakeHitbox({{offset, size}}));
}

void AddTileMetaInfo(const Tactile::IO::Tileset& irTileset,
                     entt::registry& registry,
                     comp::Tileset& tileset,
                     const int32 firstId)
{
  const auto ratio = GetTilesetTileSizeRatio(irTileset);
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
        AddHitbox(irObject, registry, tileEntity, ratio);
      }
    });
  });
}

}  // namespace

auto GetTextureId(const Tactile::IO::Tileset& irTileset) -> rune::texture_id
{
  const auto id = 1'000 + GetInt(irTileset, "id"); /* Offset ID to avoid clashes */
  return rune::texture_id(id);
}

auto GetTilesetTileSizeRatio(const Tactile::IO::Tileset& irTileset) -> float2
{
  const auto tw = Tactile::IO::GetTileWidth(irTileset);
  const auto th = Tactile::IO::GetTileHeight(irTileset);

  const auto xRatio = glob::tile_width<float> / static_cast<float>(tw);
  const auto yRatio = glob::tile_height<float> / static_cast<float>(th);

  return {xRatio, yRatio};
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

void CreateTileset(const Tactile::IO::Map& irMap,
                   comp::Level& level,
                   GraphicsContext& graphics)
{
  auto& registry = level.registry;

  level.tileset = registry.create();
  auto& tileset = registry.emplace<comp::Tileset>(level.tileset);

  Tactile::IO::EachTileset(irMap, [&](const Tactile::IO::Tileset& irTileset) {
    const auto texture = graphics.to_index(GetTextureId(irTileset));
    const auto first = Tactile::IO::GetFirstGlobalId(irTileset);
    const auto ratio = GetTilesetTileSizeRatio(irTileset);

    CreateTiles(irTileset, registry, tileset, texture);
    AddTileMetaInfo(irTileset, registry, tileset, first);
  });
}

}  // namespace wanderer
