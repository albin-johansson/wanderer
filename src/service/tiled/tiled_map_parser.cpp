#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "tile_map_impl.h"
#include "tile_map_layer_impl.h"
#include "sprite_sheet.h"
#include "bad_state_exception.h"
#include "tile_animation.h"
#include <sstream>
#include <map>

#include "tiled_tile_set.h"
#include "tiled_map.h"
#include "tiled_layer.h"

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

//std::vector<ITileMapLayer_uptr> TiledMapParser::LoadLayers(const pugi::xml_node& mapRootNode) {
//  std::vector<ITileMapLayer_uptr> layers;
//  int nLayers = 0;
//  for (auto layerNode : mapRootNode.children("layer")) {
//
//    auto nCols = layerNode.attribute("width").as_int();
//    auto nRows = layerNode.attribute("height").as_int();
//    auto data = layerNode.child("data").text().as_string();
//
//    std::vector<TileID> tileIds;
//    tileIds.reserve(nRows * nCols);
//
//    std::stringstream stream(data);
//    std::string token;
//
//    while (std::getline(stream, token, ',')) {
//      tileIds.push_back(static_cast<TileID>(std::stoi(token)));
//    }
//
//    layers.push_back(std::make_unique<TileMapLayerImpl>(tileSet, nRows, nCols, std::move(tileIds)));
//    ++nLayers;
//  }
//
//  return layers;
//}

TileSet_uptr TiledMapParser::LoadTileSet(const pugi::xml_node& mapRoot) {
  auto tileSet = std::make_unique<TileSet>(3000); // FIXME

  for (pugi::xml_node ts : mapRoot.children("tileset")) {
    const std::string tsFileName = ts.attribute("source").as_string();

    const pugi::xml_document tsDocument = LoadDocument("resources/map/world/" + tsFileName);
    const pugi::xml_node tsRoot = tsDocument.child("tileset");

    const auto tileCount = tsRoot.attribute("tilecount").as_int();
    const auto firstgid = static_cast<TileID>(ts.attribute("firstgid").as_uint());
    const auto lastgid = firstgid + static_cast<TileID>(tileCount) - 1;

    const tiled::TiledTileSet tiledTileSet(tsRoot, firstgid, lastgid);

    const int tileWidth = tsRoot.attribute("tilewidth").as_int();
    const int tileSize = tileWidth;

    const std::string path = "resources/img/" + tiledTileSet.GetImageName();
    Image_sptr sheetImage = imageGenerator.Load(path);

    const int sheetCols = tiledTileSet.GetCols();
    const TileID firstId = tiledTileSet.GetFirstTileId();
    const TileID lastId = tiledTileSet.GetLastTileId();

    int i = 0;
    for (TileID id = firstId; id <= lastId; id++, i++) {
      TileProperties properties = {sheetImage, id}; // img, id, animation, hitbox, blocked

      if (tiledTileSet.HasProperty(id, "group")) {
        SDL_Log("Tile %u belongs to group %i!", id, tiledTileSet.GetInt(id, "group"));
      }

      if (tiledTileSet.HasAnimation(id)) {
        TileAnimation animation = CreateAnimation(tiledTileSet.GetAnimation(id));
        properties.animation = animation;
        properties.animated = true;
      }

      if (tiledTileSet.HasObject(id)) {
        tiled::TiledObject object = tiledTileSet.GetObject(id);

        if (object.HasAttribute("name") &&
            object.GetAttribute("name") == "hitbox") {
          float x = std::stof(object.GetAttribute("x"));
          float y = std::stof(object.GetAttribute("y"));
          float w = std::stof(object.GetAttribute("width"));
          float h = std::stof(object.GetAttribute("height"));

          auto wscale = w / tileSize;
          auto hscale = h / tileSize;

          Rectangle hitbox(x, y, wscale * Tile::SIZE, hscale * Tile::SIZE);

          properties.hitbox = hitbox;
          properties.blocked = true;
        }
      }

      float row = i / sheetCols;
      float col = i % sheetCols;

      tileSet->Insert(id, Tile(properties), Rectangle(col * tileSize,
                                                      row * tileSize,
                                                      tileSize,
                                                      tileSize));
    }
  }

  return tileSet;
}

//void TiledMapParser::LoadTileHitbox(const pugi::xml_node& objectNode,
//                                    TileProperties& properties,
//                                    int tileSize) {
//  if (!objectNode.empty()) {
//    float x = objectNode.attribute("x").as_float();
//    float y = objectNode.attribute("y").as_float();
//    float w = objectNode.attribute("width").as_float();
//    float h = objectNode.attribute("height").as_float();
//
//    auto wscale = w / tileSize;
//    auto hscale = h / tileSize;
//
//    Rectangle hitbox(x, y, wscale * Tile::SIZE, hscale * Tile::SIZE);
//
//    properties.hitbox = hitbox;
//    properties.blocked = true;
//  }
//}

TileAnimation TiledMapParser::CreateAnimation(tiled::TiledAnimation animation) {
  TileAnimation result(animation.GetFrames().size());

  int i = 0;
  for (const auto f : animation.GetFrames()) {
    Frame frame = {static_cast<TileID>(f.tileId), static_cast<uint32_t>(f.duration)};
    result.SetFrame(i, frame);
    ++i;
  }

  return result;
}

//Image_sptr TiledMapParser::LoadSheetImage(const pugi::xml_node& imageNode) {
//  std::string source = imageNode.attribute("source").as_string();
//  std::string path = "resources/img/" + source.substr(source.find_last_of('/') + 1);
//  return imageGenerator.Load(path);
//}

std::vector<TileID> TiledMapParser::CreateTileVector(const std::vector<int>& tiles) const {
  std::vector<TileID> result;
  result.reserve(tiles.size());
  for (int i : tiles) {
    result.push_back(static_cast<TileID>(i));
  }
  return result;
}

void TiledMapParser::LoadMap() {
  pugi::xml_document mapDocument = LoadDocument(file);
  pugi::xml_node mapNode = mapDocument.child("map");

  int nCols = mapNode.attribute("width").as_int();
  int nRows = mapNode.attribute("height").as_int();

  tiled::TiledMap tmap(mapNode);

  TileSet_sptr tileSet = LoadTileSet(mapNode);
  map = std::make_unique<TileMapImpl>(tileSet, nRows, nCols, imageGenerator);

  for (auto& l : tmap.GetLayers()) {
    auto layer = std::make_unique<TileMapLayerImpl>(tileSet,
                                                    nRows,
                                                    nCols,
                                                    CreateTileVector(l->GetTiles()));
    layer->SetGroundLayer(l->GetBool("ground"));

    // TODO more properties...

    map->AddLayer(std::move(layer));
  }
}

}