#include "tile_set.h"
#include "grass_tile.h"
#include <fstream>

namespace albinjohansson::wanderer {

TileSet::TileSet(ImageGenerator& imageGenerator) {
  auto images = LoadTileImages(imageGenerator);
  tiles.insert(std::pair<int, ITile_uptr>(0, std::make_unique<GrassTile>(images.at(0), 0)));
}

TileSet::~TileSet() = default;

std::map<int, Image_sptr> TileSet::LoadTileImages(ImageGenerator& imageGenerator) {
  try {
    auto result = std::map<int, Image_sptr>();

    std::ifstream infile("resources/img/tiles.txt");
    std::string line;
    while (std::getline(infile, line)) {
      auto i = line.find(';');
      std::string id = line.substr(0, i);
      std::string path = line.substr(i + 1);

      result.insert(std::pair<int, Image_sptr>(std::stoi(id), imageGenerator.Load(path)));
    }

    infile.close();
    return result;
  } catch (std::exception& e) {
    SDL_Log("Failed to load tile images! Error: %s", e.what());
    throw;
  }
}

const ITile& TileSet::GetTile(int id) const {
  return *tiles.at(id);
}

}
