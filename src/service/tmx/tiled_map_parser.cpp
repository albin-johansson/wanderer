#include "tiled_map_parser.h"
#include "pugixml.hpp"
#include "sprite_sheet.h"
#include "bad_state_exception.h"
#include <SDL.h>
#include <string>
#include <memory>
#include <sstream>
#include <vector>
#include <cstdint>

using namespace std;

namespace albinjohansson::wanderer {

TiledMapParser::TiledMapParser() = default;

TiledMapParser::~TiledMapParser() = default;

pugi::xml_document TiledMapParser::LoadDocument(const std::string& path) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (!result) {
    throw BadStateException("Failed to load: " + path + ", Error:" + string(result.description()));
  }
  return doc;
}

unique_ptr<TileMap> TiledMapParser::LoadMap(ImageGenerator& imageGenerator, const string& file) {
  auto mapDocument = LoadDocument(file);
  auto mapRootNode = mapDocument.child("map");

  auto mapWidth = mapRootNode.attribute("width").as_int();
  auto mapHeight = mapRootNode.attribute("height").as_int();
  auto tileWidth = mapRootNode.attribute("tilewidth").as_int();
  auto tileHeight = mapRootNode.attribute("tileheight").as_int();

  struct TTS { // temp tile set
    Image_sptr img = nullptr;
    int tilecount;
    int size;
    uint16_t firstgid;
    uint16_t lastgid;
  };

  int nTiles = 0;
  vector<TTS> tmps;
  tmps.reserve(20);

  for (auto ts : mapRootNode.children("tileset")) {
    auto firstgid = static_cast<uint16_t>(ts.attribute("firstgid").as_int());
    auto source = string(ts.attribute("source").as_string());

    auto tsDocument = LoadDocument("resources/map/world/" + source); // FIXME
    auto tsRootNode = tsDocument.child("tileset");

    auto twidth = tsRootNode.attribute("tilewidth").as_int();
    auto theight = tsRootNode.attribute("tileheight").as_int();
    auto tilecount = tsRootNode.attribute("tilecount").as_int();

    auto imageNode = tsRootNode.child("image");
    auto imgSource = string(imageNode.attribute("source").as_string()); // Relative to map
    auto imgWidth = imageNode.attribute("width").as_int();
    auto imgHeight = imageNode.attribute("height").as_int();

    // TODO tile properties

    nTiles += tilecount;

    // FIXME not very pretty
    auto pathToImage = "resources/img/" + imgSource.substr(imgSource.find_last_of('/') + 1);
    Image_sptr img = imageGenerator.Load(pathToImage);

    uint16_t lastgid = firstgid + static_cast<uint16_t>(tilecount);

    TTS tts = {img, tilecount, twidth, firstgid, lastgid};
    tmps.push_back(tts);
  }

  auto images = make_unique<TileImageSet>();
  auto tileSet = make_unique<TileSet>(nTiles);

  uint16_t i = 1;
  for (auto& tts : tmps) {
    Range range = {tts.firstgid, tts.lastgid};
    images->Add(make_unique<SpriteSheet>(tts.img, range, 32));

    TileProperties properties = {tts.img, i, false};
    tileSet->Insert(i, Tile(properties));

    ++i;
  }

  vector<unique_ptr<TileMapLayer>> layers;
  int nLayers = 0;
  for (auto layerNode : mapRootNode.children("layer")) {
    auto nCols = layerNode.attribute("width").as_int();
    auto nRows = layerNode.attribute("height").as_int();
    auto data = layerNode.child("data").text().as_string();

    vector<int> tiles;
    tiles.reserve(nRows * nCols);

    stringstream stream(data);
    string token;

    while (getline(stream, token, ',')) {
      tiles.push_back(stoi(token));
    }

    layers.push_back(make_unique<TileMapLayer>(nRows, nCols, move(tiles)));
    ++nLayers;
  }

  SDL_Log("Loaded %i layers!", nLayers);

  auto tmap = make_unique<TileMap>(move(images), mapHeight, mapWidth);

  for (auto& layer : layers) {
    tmap->AddLayer(move(layer));
  }

  return tmap;
}

}
