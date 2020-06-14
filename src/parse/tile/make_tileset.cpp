#include "make_tileset.h"

#include "animated.h"
#include "make_tile.h"
#include "math.h"
#include "tileset.h"

using namespace centurion;

namespace wanderer {
namespace {

void create_tiles(entt::registry& registry,
                  Tileset& tileset,
                  const step::Tileset& stepTileset,
                  const std::shared_ptr<Texture>& sheet) noexcept
{
  auto id = static_cast<TileID>(stepTileset.first_gid());
  for (auto index = 0; index < stepTileset.tile_count(); ++index, ++id) {
    const auto [row, col] =
        Math::index_to_matrix_pos(index, stepTileset.columns());

    const auto x = col * stepTileset.tile_width();
    const auto y = row * stepTileset.tile_height();
    const IRect src{{x, y},
                    {stepTileset.tile_width(), stepTileset.tile_height()}};

    const auto tileEntity = make_basic_tile(registry, id, sheet, src);

    tileset.tiles.emplace(id, tileEntity);
  }
}

}  // namespace

entt::entity make_tileset(entt::registry& registry,
                          const std::vector<step::Tileset>& tilesets,
                          Renderer& renderer)
{
  const auto entity = registry.create();

  auto& tileset = registry.emplace<Tileset>(entity);

  for (const auto& stepTileset : tilesets) {
    const auto sheet = Texture::shared(
        renderer, ("resource/map/" + stepTileset.image()).c_str());

    create_tiles(registry, tileset, stepTileset, sheet);

    const auto firstGID = static_cast<TileID>(stepTileset.first_gid());
    for (const auto& stepTile : stepTileset.tiles()) {
      const auto gid = firstGID + static_cast<TileID>(stepTile.id());
      parse_special_tile(registry, tileset.tiles.at(gid), stepTile, firstGID);
    }
  }

  return entity;
}

}  // namespace wanderer
