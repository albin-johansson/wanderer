#include "tile_set_builder.h"
#include "tile_builder.h"
#include "pugi_utils.h"
#include "image_generator.h"
#include "image.h"

using namespace centurion;

namespace albinjohansson::wanderer {

tiled::TiledTileSet TileSetBuilder::CreateTiledTileSet(const pugi::xml_node& tileSetNode,
                                                       TileID firstId) {
  const auto tileCount = tileSetNode.attribute("tilecount").as_int();
  const auto lastgid = firstId + static_cast<TileID>(tileCount) - 1;
  return tiled::TiledTileSet(tileSetNode, firstId, lastgid);
}

std::unique_ptr<TileSet> TileSetBuilder::Create(const pugi::xml_node& mapRoot,
                                                ImageGenerator& imageGenerator) {
  const auto tsChildren = mapRoot.children("tileset");
  const auto nTilesets = std::distance(tsChildren.begin(), tsChildren.end());
  auto tileSet = std::make_unique<TileSet>(nTilesets * 1024); // Guess the amount of tiles

  for (const auto tsInfoNode : tsChildren) {
    const std::string tsFileName = tsInfoNode.attribute("source").as_string();

    const auto tsDocument = PugiUtils::LoadDocument("resources/map/world/" + tsFileName);
    const auto tileSetNode = tsDocument.child("tileset");

    const auto firstId = static_cast<TileID>(tsInfoNode.attribute("firstgid").as_uint());
    auto tiledTileSet = CreateTiledTileSet(tileSetNode, firstId);

    const auto path = "resources/img/" + tiledTileSet.GetImageName();
    std::shared_ptr<Image> image = imageGenerator.Load(path);

    const TileID lastId = tiledTileSet.GetLastTileId();
    int index = 0;

    for (TileID id = firstId; id <= lastId; id++, index++) {
      tileSet->Insert(id, TileBuilder::Create(image, tiledTileSet, id, index));
    }
  }

  return tileSet;
}

}
