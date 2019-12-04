#pragma once
#include <pugixml.hpp>
#include <string>
#include <map>

namespace albinjohansson::tiled {

class TiledMap final {
 private:
  pugi::xml_node mapNode;

 public:
  explicit TiledMap(pugi::xml_node mapNode);

  explicit TiledMap(pugi::xml_node&& mapNode);

  ~TiledMap();

  [[nodiscard]] int GetWidth() const;

  [[nodiscard]] int GetHeight() const;

  [[nodiscard]] int GetTileWidth() const;

  [[nodiscard]] int GetTileHeight() const;

};

}
