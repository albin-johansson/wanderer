#pragma once
#include "pugixml.hpp"
#include "tile_id.h"
#include "tile_animation.h"
#include <memory>
#include <string>
#include <vector>

namespace albinjohansson::tiled {

class TiledAnimation;

}

namespace albinjohansson::wanderer {

class ITileMap;
class ImageGenerator;
class TileSet;

class TiledMapParser final {
 private:
  std::unique_ptr<ITileMap> map = nullptr;
  ImageGenerator& imageGenerator;
  const std::string& file;  // FIXME shady reference fields

  void LoadMap();

  [[nodiscard]] pugi::xml_document LoadDocument(const std::string& path);

  [[nodiscard]] std::unique_ptr<TileSet> LoadTileSet(const pugi::xml_node& mapRootNode);

  [[nodiscard]] static TileAnimation CreateAnimation(tiled::TiledAnimation animation);

  [[nodiscard]] static std::vector<TileID> CreateTileVector(const std::vector<int>& tiles);

 public:
  TiledMapParser(ImageGenerator& imageGenerator, const std::string& file);

  ~TiledMapParser();

  [[nodiscard]] std::unique_ptr<ITileMap> GetMap() noexcept;
};

}
