#pragma once
#include "tile.h"
#include <SDL_render.h>

namespace wanderer::core {

/**
 * The AbstractTile class is an abstract class that partially implements the ITile interface.
 *
 * @see ITile
 * @since 0.1.0
 */
class AbstractTile : public ITile {
 private:
  const int row;
  const int col;
  const int id;

 protected:
  SDL_Texture* texture = nullptr;

  AbstractTile(int row, int col, int id);

 public:
  ~AbstractTile() override;

  void Tick(float delta) override;

  [[nodiscard]] inline Rectangle GetHitbox() const noexcept override {
    return Rectangle(GetX(), GetY(), SIZE, SIZE);
  }

  [[nodiscard]] inline int GetId() const noexcept final { return id; }

  [[nodiscard]] inline int GetRow() const noexcept final { return row; }

  [[nodiscard]] inline int GetCol() const noexcept final { return col; }

  [[nodiscard]] inline float GetX() const noexcept final {
    return static_cast<float>(col) * static_cast<float>(SIZE);
  }

  [[nodiscard]] inline float GetY() const noexcept final {
    return static_cast<float>(row) * static_cast<float>(SIZE);
  }

  [[nodiscard]] inline float GetWidth() const noexcept final { return SIZE; }

  [[nodiscard]] inline float GetHeight() const noexcept final { return SIZE; }
};

}
