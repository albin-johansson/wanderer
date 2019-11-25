#pragma once
#include "tile.h"
#include "level.h"

namespace albinjohansson::wanderer {

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
  Image_sptr image = nullptr;

  AbstractTile(int row, int col, int id);

 public:
  ~AbstractTile() override;

  void Tick(ILevel& level, float delta) override;

  void SetImage(Image_sptr image) noexcept final;

  [[nodiscard]] inline Image_sptr GetImage() const noexcept final {
    return image;
  }

  [[nodiscard]] inline Rectangle GetHitbox() const noexcept override {
    return Rectangle(GetX(), GetY(), SIZE, SIZE);
  }

  [[nodiscard]] inline int GetId() const noexcept final { return id; }

  [[nodiscard]] inline float GetX() const noexcept final { return static_cast<float>(col) * SIZE; }

  [[nodiscard]] inline float GetY() const noexcept final { return static_cast<float>(row) * SIZE; }

  [[nodiscard]] inline float GetWidth() const noexcept final { return SIZE; }

  [[nodiscard]] inline float GetHeight() const noexcept final { return SIZE; }
};

}
