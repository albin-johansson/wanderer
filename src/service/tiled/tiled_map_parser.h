#pragma once
#include "pugixml.hpp"
#include "tile_id.h"
#include "tile_map.h"
#include "tile_map_layer.h"
#include "image.h"
#include <string>
#include <vector>
#include <map>

namespace albinjohansson::tiled {

class TiledAnimation;

}

namespace albinjohansson::wanderer {

struct TileObject;

class ImageGenerator;

class TileSet;

using TileSet_sptr = std::shared_ptr<TileSet>;

class TiledMapParser final {
 private:
  ITileMap_uptr map = nullptr;
  const std::string& file;
  ImageGenerator& imageGenerator;

  void LoadMap();

  [[nodiscard]] pugi::xml_document LoadDocument(const std::string& path);

  [[nodiscard]] TileSet_uptr LoadTileSet(const pugi::xml_node& mapRootNode);

  TileAnimation CreateAnimation(tiled::TiledAnimation animation);

  [[nodiscard]] std::vector<TileID> CreateTileVector(const std::vector<int>& tiles) const;

  [[nodiscard]] std::map<int, std::vector<TileObject>> CreateTileGroups(const TileSet_sptr& tileSet,
                                                                        const std::vector<TileID>& tiles,
                                                                        int nCols);

  [[nodiscard]] std::map<int, std::vector<TileObject>> CreateRenderGroups(
      const std::vector<TileObject>& objects);

 public:

  TiledMapParser(ImageGenerator& imageGenerator, const std::string& file);

  ~TiledMapParser();

  [[nodiscard]] ITileMap_uptr GetMap() noexcept { return std::move(map); }
};

}
