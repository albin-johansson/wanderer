#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "sprite_sheet.h"
#include "bad_state_exception.h"
#include <sstream>

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

void TiledMapParser::LoadMap() {
  pugi::xml_document mapDocument = LoadDocument(file);
  pugi::xml_node mapRoot = mapDocument.child("map");

  int nCols = mapRoot.attribute("width").as_int();
  int nRows = mapRoot.attribute("height").as_int();

  std::vector<TileMapLayer_uptr> layers = LoadLayers(mapRoot);

  // Process all tile sheets

  TileSet_uptr tileSet = std::make_unique<TileSet>(3000); // FIXME

  for (pugi::xml_node ts : mapRoot.children("tileset")) {
    std::string tsFileName = ts.attribute("source").as_string();

    pugi::xml_document tsDocument = LoadDocument("resources/map/world/" + tsFileName); // FIXME
    pugi::xml_node tsRoot = tsDocument.child("tileset");

    int tileWidth = tsRoot.attribute("tilewidth").as_int();
    int tileHeight = tsRoot.attribute("tileheight").as_int();
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
//    for (pugi::xml_node t : ts.children("tile")) {
    // TODO...
//    }

    int sheetRows = sheetImage->GetHeight() / size;
    int sheetCols = sheetImage->GetHeight() / size;

    int i = 0;
    for (TileID id = firstgid; id <= lastgid; id++, i++) {
      TileProperties properties = {sheetImage, id}; // img, id, animation, hitbox, blocked

      auto row = i / sheetCols;
      auto col = i % sheetCols;
      Rectangle srcRect(col * size, row * size, size, size);

      tileSet->Insert(id, Tile(properties), srcRect);
    }
  }

  map = std::make_unique<TileMap>(std::move(tileSet), nRows, nCols);

  for (auto& layer : layers) {
    map->AddLayer(std::move(layer));
  }
}

}
