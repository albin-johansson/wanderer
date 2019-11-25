#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "tile_map_layer.h"
#include "image.h"
#include <SDL.h>
#include <string>
#include <sstream>
#include <vector>
#include <bad_state_exception.h>

namespace albinjohansson::wanderer {

TiledMapParser::TiledMapParser(ImageGenerator& imageGenerator, const std::string& file) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(file.c_str());
  if (result) {
    SDL_Log("Success reading TSX file!");
  } else {
    throw BadStateException("Failed to load tiled map! Error:" + std::string(result.description()));
  }

  auto mapNode = doc.child("map");

  for (auto tileset : mapNode.children("tileset")) {
    Image_uptr sheet = CreateTileSheet(tileset, imageGenerator, file);

    // TODO save sprite sheets.
  }

  for (auto layerNode : mapNode.children("layer")) {
    TileMapLayer layer = CreateTileMapLayer(layerNode);
  }

// TODO create tile map
}

TiledMapParser::~TiledMapParser() = default;

Image_uptr TiledMapParser::CreateTileSheet(const pugi::xml_node& sheetNode,
                                           ImageGenerator& imageGenerator,
                                           const std::string& parentPath) {
  // FIXME this method is quite bad
  auto directory = parentPath.substr(0, parentPath.find_last_of('/'));
  auto src = sheetNode.attribute("source");
  auto tsxPath = directory + "/" + std::string(src.value());

  pugi::xml_document tsxDocument;
  auto result = tsxDocument.load_file(tsxPath.c_str());

  if (!result) {
    throw BadStateException("Failed to load sheet! Error:"
                                + std::string(result.description()));
  }

  auto tilesetNode = tsxDocument.child("tileset");
  auto path = std::string(tilesetNode.child("image").attribute("source").as_string());
  path = "resources/img/" + path.substr(path.find_last_of('/') + 1);

  return imageGenerator.Load(path);
}

TileMapLayer TiledMapParser::CreateTileMapLayer(const pugi::xml_node& layerNode) {
  auto width = layerNode.attribute("width");
  auto height = layerNode.attribute("height");
  auto data = layerNode.child("data").text().as_string();

  const int nCols = width.as_int();
  const int nRows = height.as_int();

  std::vector<int> tiles;
  tiles.reserve(nCols * nRows);

  std::stringstream strStream(data);
  std::string token;

  int i = 0;
  while (std::getline(strStream, token, ',')) {
    tiles[i++] = std::stoi(token);
  }

  return TileMapLayer(nRows, nCols, std::move(tiles)); // TODO maybe return unique pointer
}

}
