#pragma once
#include "image.h"
#include "rectangle.h"
#include "tile.h"
#include <memory>
#include <unordered_map>

namespace albinjohansson::wanderer {

/**
 * A simple struct that describes a range of values.
 *
 * @since 0.1.0
 */
struct Range {
  int min;
  int max;
};

/**
 * The SpriteSheet class represents a sprite sheet that holds rectangles that represent each sprite.
 *
 * @since 0.1.0
 */
class SpriteSheet final {
 private:
  Image_sptr sheet = nullptr;
  const Range range;
  const float size;
  int nRows;
  int nCols;
  int nSprites;
  std::unordered_map<TileID, Rectangle> sourceRectangles;

 public:
  /**
   * @param sheet a shared pointer to the associated image.
   * @param range the range of
   * @param size
   * @throws NullPointerException if the supplied image pointer is null.
   */
  SpriteSheet(Image_sptr sheet, Range range, int size);

  ~SpriteSheet();

  /**
   * Returns a reference to the source rectangle associated with the supplied sprite ID.
   *
   * @param id the sprite ID of the desired source rectangle.
   * @return a reference to the source rectangle associated with the supplied sprite ID.
   * @throws out_of_range if the sprite ID isn't located in the sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]] const Rectangle& GetSource(TileID id) const;

  /**
   * Returns the minimum sprite ID value contained in the sprite sheet.
   *
   * @return the minimum sprite ID value contained in the sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]] int GetMinId() const noexcept { return range.min; }

  /**
   * Returns the maximum sprite ID value contained in the sprite sheet.
   *
   * @return the maximum sprite ID value contained in the sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]] int GetMaxId() const noexcept { return range.max; }

  /**
   * Returns the number of rows in the sprite sheet.
   *
   * @return the number of rows in the sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]] int GetRows() const noexcept { return nRows; }

  /**
   * Returns the number of columns in the sprite sheet.
   *
   * @return the number of columns in the sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]] int GetCols() const noexcept { return nCols; }

  /**
   * Indicates whether or not the sprite sheet contains the supplied sprite ID.
   *
   * @param id the sprite ID that will be checked.
   * @return true if the supplied ID is contained in the sprite sheet; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]] bool Contains(TileID id) const noexcept {
    return (id >= range.min) && (id <= range.max);
  }

  /**
   * Returns the size of each sprite in the sprite sheet.
   *
   * @return the size of each sprite in the sprite sheet.
   * @since 0.1.0
   */
  [[nodiscard]] float GetSpriteSize() const noexcept { return size; }

  /**
   * Returns a pointer to the associated image.
   *
   * @return a shared pointer to the associated image.
   * @since 0.1.0
   */
  [[nodiscard]] Image_sptr GetImage() noexcept { return sheet; }
};

using SpriteSheet_uptr = std::unique_ptr<SpriteSheet>;
using SpriteSheet_sptr = std::shared_ptr<SpriteSheet>;
using SpriteSheet_wptr = std::weak_ptr<SpriteSheet>;

}
