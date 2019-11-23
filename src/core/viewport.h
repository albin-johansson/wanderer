#pragma once
#include "rectangle.h"

namespace albinjohansson::wanderer {

/**
   * A simple struct that describes an area, using floating-point values.
   *
   * @since 0.1.0
   */
struct Area {
  float width;
  float height;
};

/**
 * The Viewport class represents the area that the user sees of the game world.
 *
 * @since 0.1.0
 */
class Viewport final {
 private:
  Rectangle bounds;
  Area level;

 public:
  /**
   * Constructs a viewport with the bounds (0, 0, 10, 10) and level dimensions 10x10.
   *
   * @since 0.1.0
   */
  Viewport();

  /**
   * Constructs a viewport. A dimension that isn't greater than zero will cause an exception to be
   * thrown.
   *
   * @param viewport the viewport area.
   * @param level the level area.
   * @throws invalid_argument if any dimension isn't greater than zero.
   * @since 0.1.0
   */
  Viewport(Area viewport, Area level);

  /**
   * Tracks the viewport towards the object with the specified properties.
   *
   * @param tx the target x-coordinate.
   * @param ty the target y-coordinate.
   * @param size the size of the target.
   * @param delta the delta time, in seconds.
   * @since 0.1.0
   */
  void Track(float tx, float ty, Area size, float delta) noexcept;

  /**
   * Sets the width of the viewport.
   *
   * @param width the new width of the viewport.
   * @throws invalid_argument if the width isn't greater than zero.
   * @since 0.1.0
   */
  void SetWidth(float width);

  /**
   * Sets the height of the viewport.
   *
   * @param height the new height of the viewport.
   * @throws invalid_argument if the height isn't greater than zero.
   * @since 0.1.0
   */
  void SetHeight(float height);

  /**
   * Sets the width of the level.
   *
   * @param levelWidth the width of the level.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetLevelWidth(float levelWidth);

  /**
   * Sets the height of the level.
   *
   * @param levelHeight the height of the level.
   * @throws invalid_argument if the supplied height isn't greater than zero.
   * @since 0.1.0
   */
  void SetLevelHeight(float levelHeight);

  /**
   * Returns the current bounds of the viewport.
   *
   * @return the current bounds of the viewport.
   * @since 0.1.0
   */
  [[nodiscard]] inline Rectangle GetBounds() const noexcept { return bounds; }

  /**
   * Calculates and returns the translated value for the supplied x-coordinate.
   *
   * @param x the value that will be translated.
   * @return the translated value for the supplied x-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetTranslatedX(float x) const noexcept {
    return x - bounds.GetX();
  }

  /**
   * Calculates and returns the translated value for the supplied y-coordinate.
   *
   * @param y the value that will be translated.
   * @return the translated value for the supplied y-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]] inline float GetTranslatedY(float y) const noexcept {
    return y - bounds.GetY();
  }
};

}
