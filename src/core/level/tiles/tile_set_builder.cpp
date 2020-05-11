#include "tile_set_builder.h"

#include "pugi_utils.h"
#include "tile_builder.h"

using namespace centurion;

namespace albinjohansson::wanderer {

tiled::TiledTileSet TileSetBuilder::create_tiled_tile_set(
    const pugi::xml_node& tileSetNode, TileID firstId)
{
  const auto tileCount = tileSetNode.attribute("tilecount").as_int();
  const auto lastgid = firstId + static_cast<TileID>(tileCount) - 1;
  return tiled::TiledTileSet(tileSetNode, firstId, lastgid);
}

unique<TileSet> TileSetBuilder::create(const pugi::xml_node& mapRoot,
                                       TextureLoader& textureLoader)
{
  const auto tsChildren = mapRoot.children("tileset");
  const auto nTilesets = std::distance(tsChildren.begin(), tsChildren.end());
  auto tileSet =
      std::make_unique<TileSet>(nTilesets * 1024);  // Guess the amount of tiles

  for (const auto tsInfoNode : tsChildren) {
    const std::string tsFileName = tsInfoNode.attribute("source").as_string();

    const auto tsDocument =
        PugiUtils::LoadDocument("resources/map/world/" + tsFileName);
    const auto tileSetNode = tsDocument.child("tileset");

    const auto firstId =
        static_cast<TileID>(tsInfoNode.attribute("firstgid").as_uint());
    auto tiledTileSet = create_tiled_tile_set(tileSetNode, firstId);

    const auto path = "resources/img/" + tiledTileSet.get_image_name();
    auto image = textureLoader.shared_img(path.c_str());

    const auto lastId = static_cast<TileID>(tiledTileSet.get_last_tile_id());
    int index = 0;

    for (TileID id = firstId; id <= lastId; id++, index++) {
      tileSet->insert(id, TileBuilder::create(image, tiledTileSet, id, index));
    }
  }

  return tileSet;
}

}  // namespace albinjohansson::wanderer
