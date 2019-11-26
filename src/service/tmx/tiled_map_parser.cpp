#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "tile_map_layer.h"
#include "image.h"
#include "sprite_sheet.h"
#include "tile_image_set.h"
#include <SDL.h>
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <bad_state_exception.h>

namespace albinjohansson::wanderer {

TiledMapParser::TiledMapParser() = default;

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

std::unique_ptr<TileMapLayer> TiledMapParser::CreateTileMapLayer(const pugi::xml_node& layerNode) {
  auto width = layerNode.attribute("width");
  auto height = layerNode.attribute("height");
  auto data = layerNode.child("data").text().as_string();

  const int nCols = width.as_int();
  const int nRows = height.as_int();

  std::vector<int> tiles;
  tiles.reserve(nCols * nRows + 1);

  std::stringstream strStream(data);
  std::string token;

  while (std::getline(strStream, token, ',')) {
    tiles.push_back(std::stoi(token));

    // TODO create tile set with properties for collisions, animations, etc...
  }

  return std::make_unique<TileMapLayer>(nRows, nCols, tiles);
}

std::unique_ptr<TileMap> TiledMapParser::LoadMap(ImageGenerator& imageGenerator,
                                                 const std::string& file) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(file.c_str());
  if (result) {
    SDL_Log("Success reading TSX file!");
  } else {
    throw BadStateException("Failed to load tiled map! Error:" + std::string(result.description()));
  }

  auto mapNode = doc.child("map");

  auto imageSet = std::make_unique<TileImageSet>();

  int accumulator = 0;
  for (auto tileset : mapNode.children("tileset")) {
    auto firstID = tileset.attribute("firstgid").as_int();

    accumulator += firstID;

    Image_uptr img = CreateTileSheet(tileset, imageGenerator, file);
    Range range = {accumulator, accumulator + 1024}; // FIXME

    imageSet->Add(std::make_unique<SpriteSheet>(std::move(img), range, 32));
  }

  auto map = std::make_unique<TileMap>(std::move(imageSet), 50, 50); // FIXME
  for (auto layerNode : mapNode.children("layer")) {
    map->AddLayer(CreateTileMapLayer(layerNode));
  }

  return map;
}

}
