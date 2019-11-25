#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "tile_map_layer.h"
#include <SDL.h>
#include <string>
#include <sstream>
#include <vector>

namespace albinjohansson::wanderer {

TiledMapParser::TiledMapParser(const std::string& file) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(file.c_str());
  if (result) {
    SDL_Log("Success reading TSX file!");
  } else {
    SDL_Log("Failed to open TSX document from %s. Error: %s", file.c_str(), result.description());
  }

  auto mapNode = doc.child("map");

  for (pugi::xml_node tileset : mapNode.children("tileset")) {
    auto firstId = tileset.attribute("firstgid");
    auto src = tileset.attribute("source");

    // TODO create sprite sheets
  }

  for (auto layer : mapNode.children("layer")) {
//    auto id = layer.attribute("id");
//    auto name = layer.attribute("name");
    auto width = layer.attribute("width");
    auto height = layer.attribute("height");

    auto data = layer.child("data").text().as_string();

    int nCols = width.as_int();
    int nRows = height.as_int();

    std::vector<int> tiles;
    tiles.reserve(nCols * nRows);

    std::stringstream strStream(data);
    std::string token;

    int i = 0;
    while (std::getline(strStream, token, ',')) {
      tiles[i++] = std::stoi(token);
    }

    tiles.shrink_to_fit();
    TileMapLayer tmLayer(nRows, nCols, std::move(tiles));
  }

}

TiledMapParser::~TiledMapParser() = default;

}
