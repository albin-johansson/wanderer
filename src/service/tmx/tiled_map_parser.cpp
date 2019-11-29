#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "sprite_sheet.h"
#include "bad_state_exception.h"
#include <sstream>

namespace albinjohansson::wanderer {

TiledMapParser::TiledMapParser() = default;

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

std::vector<TTS> TiledMapParser::CreateTileSetInfo(ImageGenerator& imageGenerator,
                                                   const pugi::xml_node& mapRootNode) {
  std::vector<TTS> tmps;
  tmps.reserve(20);

  for (auto ts : mapRootNode.children("tileset")) {
    auto firstgid = static_cast<uint16_t>(ts.attribute("firstgid").as_int());
    auto source = std::string(ts.attribute("source").as_string());

    auto tsDocument = LoadDocument("resources/map/world/" + source); // FIXME
    auto tsRootNode = tsDocument.child("tileset");

    auto twidth = tsRootNode.attribute("tilewidth").as_int();
//    auto theight = tsRootNode.attribute("tileheight").as_int();
    auto tilecount = tsRootNode.attribute("tilecount").as_int();

    auto imageNode = tsRootNode.child("image");
    auto imgSource = std::string(imageNode.attribute("source").as_string()); // Relative to map
//    auto imgWidth = imageNode.attribute("width").as_int();
//    auto imgHeight = imageNode.attribute("height").as_int();

    // TODO tile properties

    nTiles += tilecount;

    // FIXME not very pretty
    auto pathToImage = "resources/img/" + imgSource.substr(imgSource.find_last_of('/') + 1);
    Image_sptr img = imageGenerator.Load(pathToImage);

    uint16_t lastgid = firstgid + static_cast<uint16_t>(tilecount);

    TTS tts = {img, tilecount, twidth, firstgid, lastgid};
    tmps.push_back(tts);
  }

  return tmps;
}

std::vector<std::unique_ptr<TileMapLayer>> TiledMapParser::CreateTileMapLayers(const pugi::xml_node& mapRootNode) {

  std::vector<std::unique_ptr<TileMapLayer>> layers;
  int nLayers = 0;
  for (auto layerNode : mapRootNode.children("layer")) {
    auto nCols = layerNode.attribute("width").as_int();
    auto nRows = layerNode.attribute("height").as_int();
    auto data = layerNode.child("data").text().as_string();

    std::vector<int> tileIds;
    tileIds.reserve(nRows * nCols);

    std::stringstream stream(data);
    std::string token;

    while (std::getline(stream, token, ',')) {
      tileIds.push_back(std::stoi(token));
    }

    layers.push_back(std::make_unique<TileMapLayer>(nRows, nCols, std::move(tileIds)));
    ++nLayers;
  }

  return layers;
}

void TiledMapParser::PrepareTileSets(const std::vector<TTS>& tempTileSets,
                                     TileSet& tileSet,
                                     TileImageSet& imageSet) {
  uint16_t tileId = 1;
  for (auto& tts : tempTileSets) {
    Range range = {tts.firstgid, tts.lastgid};
    imageSet.Add(std::make_unique<SpriteSheet>(tts.img, range, 32));

    TileProperties properties = {tts.img, tileId, false};
    tileSet.Insert(tileId, Tile(properties));

    ++tileId;
  }
}

std::unique_ptr<TileMap> TiledMapParser::LoadMap(ImageGenerator& imageGenerator,
                                                 const std::string& file) {
  auto mapDocument = LoadDocument(file);
  auto mapRootNode = mapDocument.child("map");

  auto mapWidth = mapRootNode.attribute("width").as_int();
  auto mapHeight = mapRootNode.attribute("height").as_int();
//  auto tileWidth = mapRootNode.attribute("tilewidth").as_int();
//  auto tileHeight = mapRootNode.attribute("tileheight").as_int();

  std::vector<TTS> tempTileSets = CreateTileSetInfo(imageGenerator, mapRootNode);

  auto tileImageSet = std::make_unique<TileImageSet>();
  auto tileSet = std::make_unique<TileSet>(nTiles);

  PrepareTileSets(tempTileSets, *tileSet, *tileImageSet);

  auto tileMap = std::make_unique<TileMap>(std::move(tileImageSet), mapHeight, mapWidth);

  for (auto& layer : CreateTileMapLayers(mapRootNode)) {
    tileMap->AddLayer(std::move(layer));
  }

  return tileMap;
}

}
