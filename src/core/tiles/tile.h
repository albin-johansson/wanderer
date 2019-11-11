#pragma once
#include "game_object.h"
#include "drawable.h"
#include <memory>

namespace wanderer::core {

// TODO see the solution Notch used for one of his ludum dare games, where only the ID is stored
//  and there are only one actual instance of the Tile class that describes the different types.

class Tile : public IGameObject {
 private:
  int row;
  int col;
  int id;

 public:
  static constexpr int SIZE = 200;

  Tile(int row, int col, int id);

  ~Tile() override = default;

  void Tick(float delta) override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override;

  Rectangle GetHitbox() const noexcept override;

  [[nodiscard]] inline float GetX() const noexcept override {
    return static_cast<float>(col) * SIZE;
  }

  [[nodiscard]] inline float GetY() const noexcept override {
    return static_cast<float>(row) * SIZE;
  }

  [[nodiscard]] inline int GetWidth() const noexcept override { return SIZE; }

  [[nodiscard]] inline int GetHeight() const noexcept override { return SIZE; }

  [[nodiscard]] inline int GetRow() const noexcept { return row; }

  [[nodiscard]] inline int GetCol() const noexcept { return col; }

  [[nodiscard]] inline int GetId() const noexcept { return id; }
};

using Tile_uptr = std::unique_ptr<Tile>;
using Tile_sptr = std::shared_ptr<Tile>;
using Tile_wptr = std::weak_ptr<Tile>;

}
