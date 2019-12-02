#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "sprite_sheet.h"
#include "bad_state_exception.h"
#include <sstream>
#include <map>

namespace albinjohansson::wanderer {

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

std::vector<TileMapLayer_uptr> TiledMapParser::LoadLayers(const pugi::xml_node& mapRootNode) {

  std::vector<TileMapLayer_uptr> layers;
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

    layers.push_back(std::make_unique<TileMapLayer>(nRows, nCols, std::move(tileIds)));
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

    int tileWidth = tsRoot.attribute("tilewidth").as_int();
//    int tileHeight = tsRoot.attribute("tileheight").as_int();
    int tileCount = tsRoot.attribute("tilecount").as_int();

    auto size = tileWidth;

    TileID firstgid = static_cast<TileID>(ts.attribute("firstgid").as_uint());
    TileID lastgid = firstgid + static_cast<TileID>(tileCount) - 1;

    // Tile sheet image
    pugi::xml_node img = tsRoot.child("image");

    // FIXME ugly file paths
    std::string imgPath = img.attribute("source").as_string();
    std::string pathToImage = "resources/img/" + imgPath.substr(imgPath.find_last_of('/') + 1);
    Image_sptr sheetImage = imageGenerator.Load(pathToImage);

    // Process special tile properties
    for (pugi::xml_node t : tsRoot.children("tile")) {
      TileID specialId = firstgid + static_cast<TileID>(t.attribute("id").as_uint());
      TileProperties props;

      pugi::xml_node anim = t.child("animation");
      if (!anim.empty()) {

        props.animated = true;

        // TODO...
      }

      pugi::xml_node obj = t.child("objectgroup").child("object");
      if (!obj.empty()) {
        float x = obj.attribute("x").as_float();
        float y = obj.attribute("y").as_float();
        float w = obj.attribute("width").as_float();
        float h = obj.attribute("height").as_float();

        auto wscale = w / size;
        auto hscale = h / size;

        Rectangle rect(x, y, wscale * Tile::SIZE, hscale * Tile::SIZE);

        props.hitbox = rect;
        props.blocked = true;
      }

      specialProperties.insert(std::pair<TileID, TileProperties>(specialId, props));
    }

//    int sheetRows = sheetImage->GetHeight() / size;
    int sheetCols = sheetImage->GetHeight() / size;

    int i = 0;
    for (TileID id = firstgid; id <= lastgid; id++, i++) {
      TileProperties properties = {sheetImage, id}; // img, id, animation, hitbox, blocked

      if (specialProperties.count(id)) {
        const TileProperties& tp = specialProperties.at(id);

        properties.hitbox = tp.hitbox;
        properties.blocked = tp.blocked;
        properties.animated = tp.animated;
        properties.animation = tp.animation;
      }

      auto row = i / sheetCols;
      auto col = i % sheetCols;
      Rectangle srcRect(col * size, row * size, size, size);

      tileSet->Insert(id, Tile(properties), srcRect);
    }
  }

  return tileSet;
}

void TiledMapParser::LoadMap() {
  pugi::xml_document mapDocument = LoadDocument(file);
  pugi::xml_node mapRoot = mapDocument.child("map");

  int nCols = mapRoot.attribute("width").as_int();
  int nRows = mapRoot.attribute("height").as_int();

  map = std::make_unique<TileMap>(LoadTileSet(mapRoot), nRows, nCols);

  std::vector<TileMapLayer_uptr> layers = LoadLayers(mapRoot);
  for (auto& layer : layers) {
    map->AddLayer(std::move(layer));
  }
}

}