#pragma once
#include "game_object.h"
#include "drawable.h"
#include "image.h"
#include <cstdint>
#include <memory>

namespace albinjohansson::wanderer {

struct TilePos {
  int row = 0;
  int col = 0;
};

struct TileProperties {
  Image_sptr sheet;
  uint16_t id;
  bool blocked;
};

class Tile {
 private:
  TileProperties properties;

 public:
  static constexpr float SIZE = 64;

  explicit Tile(TileProperties properties);

  ~Tile();

  void Draw(TilePos pos, Renderer& renderer, const Viewport& viewport) const;

  void Tick(ILevel& level);

  [[nodiscard]] Image& GetImage() const noexcept { return *properties.sheet; }

  /**
   * Returns the type ID the tile.
   *
   * @return the type ID the tile.
   * @since 0.1.0
   */
  [[nodiscard]] int GetId() const noexcept { return properties.id; }

  /**
   * Indicates whether or not the tile is blocked.
   *
   * @return true if the tile is blocked; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool IsBlocked() const noexcept { return properties.blocked; }
};

using ITile_uptr = std::unique_ptr<Tile>;
using ITile_sptr = std::shared_ptr<Tile>;
using ITile_wptr = std::weak_ptr<Tile>;

}
