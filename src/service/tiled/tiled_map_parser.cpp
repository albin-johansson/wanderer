#include "tiled_map_parser.h"
#include "tiled_tile_set.h"
#include "tiled_map.h"
#include "tiled_animation.h"
#include "image_generator.h"
#include "image.h"
#include "bad_state_exception.h"
#include "tile_map_impl.h"
#include "tile_map_layer_impl.h"
#include "tile_object.h"
#include "tile_set.h"

namespace albinjohansson::wanderer {

// TODO entity parsing, item parsing...

TiledMapParser::TiledMapParser(ImageGenerator& imageGenerator, const std::string& file)
    : imageGenerator(imageGenerator), file(file) {
  LoadMap();
}

TiledMapParser::~TiledMapParser() = default;

pugi::xml_document TiledMapParser::LoadDocument(const std::string& path) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (!result) {
    throw BadStateException("Failed to load: " + path + ", Error:"
                                + std::string(result.description()));
  }
  return doc;
}

std::unique_ptr<TileSet> TiledMapParser::LoadTileSet(const pugi::xml_node& mapRoot) {
  auto tileSet = std::make_unique<TileSet>(3000); // FIXME

  for (pugi::xml_node tsInfoNode : mapRoot.children("tileset")) {
    const std::string tsFileName = tsInfoNode.attribute("source").as_string();

    const pugi::xml_document tsDocument = LoadDocument("resources/map/world/" + tsFileName);
    const pugi::xml_node tileSetNode = tsDocument.child("tileset");

    const auto firstId = static_cast<TileID>(tsInfoNode.attribute("firstgid").as_uint());
    tiled::TiledTileSet tiledTileSet = CreateTiledTileSet(tileSetNode, firstId);

    const int tileWidth = tileSetNode.attribute("tilewidth").as_int();
    const int tileSize = tileWidth;

    const auto path = "resources/img/" + tiledTileSet.GetImageName();
    std::shared_ptr<Image> image = imageGenerator.Load(path);

    const TileID lastId = tiledTileSet.GetLastTileId();
    int index = 0;

    for (TileID id = firstId; id <= lastId; id++, index++) {
      tileSet->Insert(id, CreateTile(image, id, index, tileSize, tiledTileSet));
    }
  }

  return tileSet;
}

tiled::TiledTileSet TiledMapParser::CreateTiledTileSet(const pugi::xml_node& tileSetNode,
                                                       TileID firstId) {
  const auto tileCount = tileSetNode.attribute("tilecount").as_int();
  const auto lastgid = firstId + static_cast<TileID>(tileCount) - 1;
  return tiled::TiledTileSet(tileSetNode, firstId, lastgid);
}

Tile TiledMapParser::CreateTile(const std::shared_ptr<Image>& image,
                                TileID id,
                                int index,
                                int size,
                                const tiled::TiledTileSet& tiledTileSet) {
  Tile tile;

  tile.SetSheet(image);
  tile.SetId(id);

  if (tiledTileSet.HasTile(id)) {
    const auto& tiledTile = tiledTileSet.GetTile(id);

    if (tiledTile.HasProperty("depth")) {
      tile.SetDepth(tiledTile.GetIntProperty("depth"));
    }

    if (tiledTile.HasAttribute("type")) {
      tile.SetObject(tiledTile.GetStringAttribute("type") == "Object");
    }

    if (tiledTile.IsAnimated()) {
      tile.SetAnimation(CreateAnimation(tiledTile.GetAnimation()));
      tile.SetAnimated(true);
    }

    if (tiledTile.HasObject("hitbox")) {
      const auto& object = tiledTile.GetObject("hitbox");

      const auto x = (std::stof(object.GetAttribute("x")) / size) * Tile::SIZE;
      const auto y = (std::stof(object.GetAttribute("y")) / size) * Tile::SIZE;
      const auto w = (std::stof(object.GetAttribute("width")) / size) * Tile::SIZE;
      const auto h = (std::stof(object.GetAttribute("height")) / size) * Tile::SIZE;

      tile.AddRectangle(Rectangle(x, y, w, h), Vector2(x, y));
      tile.SetBlocked(true);
    }
  }

  const int x = (index % tiledTileSet.GetCols()) * size;
  const int y = (index / tiledTileSet.GetCols()) * size;
  tile.SetSource(Rectangle(x, y, size, size));

  return tile;
}

TileAnimation TiledMapParser::CreateAnimation(tiled::TiledAnimation animation) {
  const auto& frames = animation.GetFrames();
  TileAnimation result(frames.size());

  int i = 0;
  for (const auto frame : frames) {
    result.SetFrame(i, Frame{static_cast<TileID>(frame.tileId),
                             static_cast<uint32_t>(frame.duration)});
    ++i;
  }

  return result;
}

std::vector<TileID> TiledMapParser::CreateTileVector(const std::vector<int>& tiles) {
  std::vector<TileID> result;
  result.reserve(tiles.size());
  for (int i : tiles) {
    result.push_back(static_cast<TileID>(i));
  }
  return result;
}

void TiledMapParser::LoadMap() {
  const auto mapDocument = LoadDocument(file);
  const auto mapNode = mapDocument.child("map");
  const auto nCols = mapNode.attribute("width").as_int();
  const auto nRows = mapNode.attribute("height").as_int();

  tiled::TiledMap tiledMap(mapNode);

  std::shared_ptr<TileSet> tileSet = LoadTileSet(mapNode);
  map = std::make_unique<TileMapImpl>(tileSet, nRows, nCols, imageGenerator);

  for (const auto& tiledLayer : tiledMap.GetLayers()) {
    auto layer = std::make_unique<TileMapLayerImpl>(tileSet,
                                                    nRows,
                                                    nCols,
                                                    CreateTileVector(tiledLayer->GetTiles()));
    layer->SetGroundLayer(tiledLayer->GetBool("ground"));
    map->AddLayer(std::move(layer));
  }
}

std::unique_ptr<ITileMap> TiledMapParser::GetMap() noexcept { return std::move(map); }

}