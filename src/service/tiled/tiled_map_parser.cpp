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

std::vector<ITileMapLayer_uptr> TiledMapParser::LoadLayers(const pugi::xml_node& mapRootNode) {
  std::vector<ITileMapLayer_uptr> layers;
  int nLayers = 0;
  for (auto layerNode : mapRootNode.children("layer")) {
    auto nCols = layerNode.attribute("width").as_int();
    auto nRows = layerNode.attribute("height").as_int();
    auto data = layerNode.child("data").text().as_string();

    std::vector<TileID> tileIds;
    tileIds.reserve(nRows * nCols);

    std::stringstream stream(data);
    std::string token;

    while (std::getline(stream, token, ',')) {
      tileIds.push_back(static_cast<TileID>(std::stoi(token)));
    }

    layers.push_back(std::make_unique<TileMapLayerImpl>(nRows, nCols, std::move(tileIds)));
    ++nLayers;
  }

  return layers;
}

TileSet_uptr TiledMapParser::LoadTileSet(const pugi::xml_node& mapRoot) {
  TileSet_uptr tileSet = std::make_unique<TileSet>(3000); // FIXME
  std::map<TileID, TileProperties> specialProperties;

  for (pugi::xml_node ts : mapRoot.children("tileset")) {
    std::string tsFileName = ts.attribute("source").as_string();

    pugi::xml_document tsDocument = LoadDocument("resources/map/world/" + tsFileName); // FIXME
    pugi::xml_node tsRoot = tsDocument.child("tileset");

//    int tileHeight = tsRoot.attribute("tileheight").as_int();
    const int tileCount = tsRoot.attribute("tilecount").as_int();

    TileID firstgid = static_cast<TileID>(ts.attribute("firstgid").as_uint());
    TileID lastgid = firstgid + static_cast<TileID>(tileCount) - 1;

    tiled::TiledTileSet tts(tsRoot, firstgid, lastgid); // TODO switch to using the tiled:: comps

    const int tileWidth = tsRoot.attribute("tilewidth").as_int();
    const int tileSize = tileWidth;

    Image_sptr sheetImage = LoadSheetImage(tsRoot.child("image"));

    const int sheetCols = tts.GetCols();

//    LoadSpecialProperties(tsRoot, specialProperties, firstgid, tileSize);

    int i = 0;
    for (TileID id = firstgid; id <= lastgid; id++, i++) {
      TileProperties properties = {sheetImage, id}; // img, id, animation, hitbox, blocked

      if (tts.HasAnimation(id)) {
        TileAnimation animation = CreateAnimation(tts.GetAnimation(id));
        properties.animation = animation;
        properties.animated = true;
      }

      if (tts.HasObject(id)) {
        tiled::TiledObject object = tts.GetObject(id);

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

void TiledMapParser::LoadTileHitbox(const pugi::xml_node& objectNode,
                                    TileProperties& properties,
                                    int tileSize) {
  if (!objectNode.empty()) {
    float x = objectNode.attribute("x").as_float();
    float y = objectNode.attribute("y").as_float();
    float w = objectNode.attribute("width").as_float();
    float h = objectNode.attribute("height").as_float();

    auto wscale = w / tileSize;
    auto hscale = h / tileSize;

    Rectangle hitbox(x, y, wscale * Tile::SIZE, hscale * Tile::SIZE);

    properties.hitbox = hitbox;
    properties.blocked = true;
  }
}

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

Image_sptr TiledMapParser::LoadSheetImage(const pugi::xml_node& imageNode) {
  // FIXME ugly file paths
  std::string source = imageNode.attribute("source").as_string();
  std::string path = "resources/img/" + source.substr(source.find_last_of('/') + 1);
  return imageGenerator.Load(path);
}

void TiledMapParser::LoadMap() {
  pugi::xml_document mapDocument = LoadDocument(file);
  pugi::xml_node mapRootNode = mapDocument.child("map");

  int nCols = mapRootNode.attribute("width").as_int();
  int nRows = mapRootNode.attribute("height").as_int();

  map = std::make_unique<TileMapImpl>(LoadTileSet(mapRootNode), nRows, nCols, imageGenerator);

  std::vector<ITileMapLayer_uptr> layers = LoadLayers(mapRootNode);
  for (auto& layer : layers) {
    map->AddLayer(std::move(layer));
  }
}

}