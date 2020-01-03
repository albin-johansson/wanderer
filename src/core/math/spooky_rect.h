#pragma once
#include <type_traits>
#include <variant>

namespace albinjohansson::wanderer {

template<typename T = float>
class SpookyRect {
  static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>,
                "SpookyRect only accepts integers and floating point values!");
  static_assert(sizeof(int) == sizeof(float),
                "SpookyRect requires that sizeof(int) == sizeof(float)!");
  static_assert(sizeof(T) == sizeof(int),
                "SpookyRect only allows types that have the same size as int and float!");

  struct FloatRect;

  struct IntRect {
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;

    IntRect() = default;

    ~IntRect() = default;

    operator FloatRect() {
      return {static_cast<float>(x),
              static_cast<float>(y),
              static_cast<float>(w),
              static_cast<float>(h)};
    }
  };

  struct FloatRect {
    float x = 0;
    float y = 0;
    float w = 0;
    float h = 0;

    FloatRect() = default;

    ~FloatRect() = default;

    operator IntRect() {
      return {static_cast<int>(x),
              static_cast<int>(y),
              static_cast<int>(w),
              static_cast<int>(h)};
    }
  };

  std::variant<IntRect, FloatRect> rect;

 public:
  SpookyRect() {
    if constexpr (std::is_integral_v<T>) {
      rect = IntRect();
    } else {
      rect = FloatRect();
    }
  }

  SpookyRect(const SpookyRect<T>& other) {
    SetX(other.GetX());
    SetY(other.GetY());
    SetWidth(other.GetWidth());
    SetHeight(other.GetHeight());
  }

  SpookyRect(T x, T y, T width, T height) {
    SetX(x);
    SetY(y);
    SetWidth(width);
    SetHeight(height);
  }

  ~SpookyRect() = default;

  /**
   * Moves the rectangle by the specified amount along the x-axis.
   *
   * @param dx the x-axis offset, may be negative.
   * @since 0.1.0
   */
  void MoveX(T dx) noexcept {
    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      r.x += dx;
    } else {
      auto& r = std::get<FloatRect>(rect);
      r.x += dx;
    }
  }

  /**
   * Moves the rectangle by the specified amount along the y-axis.
   *
   * @param dy the y-axis offset, may be negative.
   * @since 0.1.0
   */
  void MoveY(T dy) noexcept {
    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      r.y += dy;
    } else {
      auto& r = std::get<FloatRect>(rect);
      r.y += dy;
    }
  }

//  /**
//   * Copies all of the values from the other rectangle to this rectangle.
//   *
//   * @param other the rectangle that will be copied.
//   * @since 0.1.0
//   */
//  void Set(const FRectangle& other) noexcept;

  /**
   * Sets the x-coordinate of the rectangle.
   *
   * @param x the new x-coordinate of the rectangle.
   * @since 0.1.0
   */
  void SetX(T x) noexcept {
    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      r.x = x;
    } else {
      auto& r = std::get<FloatRect>(rect);
      r.x = x;
    }
  }

  /**
   * Sets the y-coordinate of the rectangle.
   *
   * @param x the new y-coordinate of the rectangle.
   * @since 0.1.0
   */
  void SetY(T y) noexcept {
    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      r.y = y;
    } else {
      auto& r = std::get<FloatRect>(rect);
      r.y = y;
    }
  }

  /**
   * Sets the width of the rectangle.
   *
   * @param x the new width of the rectangle.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetWidth(T width) {
    if (width <= 0) {
      throw std::invalid_argument("Width must be greater than zero!");
    }

    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      r.w = width;
    } else {
      auto& r = std::get<FloatRect>(rect);
      r.w = width;
    }
  }

  /**
   * Sets the height of the rectangle.
   *
   * @param x the new height of the rectangle.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 0.1.0
   */
  void SetHeight(T height) {
    if (height <= 0) {
      throw std::invalid_argument("Height must be greater than zero!");
    }

    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      r.h = height;
    } else {
      auto& r = std::get<FloatRect>(rect);
      r.h = height;
    }
  }

  /**
   * Indicates whether or not the rectangle contains the point represented by the supplied
   * coordinates.
   *
   * @param px the x-coordinate of the point that will be checked.
   * @param py the y-coordinate of the point that will be checked.
   * @return true if the supplied point is contained in the rectangle; false otherwise.
   */
  [[nodiscard]]
  bool Contains(T px, T py) const noexcept {
    return !(px < GetX() || py < GetY() || px > GetMaxX() || py > GetMaxY());
  }

  /**
   * Indicates whether or not the rectangle intersects the supplied rectangle.
   *
   * @param rectangle the rectangle to check for an intersection.
   * @return true if the rectangle intersects the supplied rectangle; false otherwise.
   * @since 0.1.0
   */
  [[nodiscard]]
  bool Intersects(const SpookyRect<T>& other) const noexcept {
    return !(GetX() >= other.GetMaxX()
        || GetMaxX() <= other.GetX()
        || GetY() >= other.GetMaxY()
        || GetMaxY() <= other.GetY());
  }

  /**
   * Returns the x-coordinate of the rectangle.
   *
   * @return the x-coordinate of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]]
  float GetX() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      return std::get<IntRect>(rect).x;
    } else {
      return std::get<FloatRect>(rect).x;
    }
  }

  /**
   * Returns the y-coordinate of the rectangle.
   *
   * @return the y-coordinate of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]]
  float GetY() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      return std::get<IntRect>(rect).y;
    } else {
      return std::get<FloatRect>(rect).y;
    }
  }

  /**
   * Returns the width of the rectangle.
   *
   * @return the width of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]]
  float GetWidth() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      return std::get<IntRect>(rect).w;
    } else {
      return std::get<FloatRect>(rect).w;
    }
  }

  /**
   * Returns the height of the rectangle.
   *
   * @return the height of the rectangle.
   * @since 0.1.0
   */
  [[nodiscard]]
  float GetHeight() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      return std::get<IntRect>(rect).h;
    } else {
      return std::get<FloatRect>(rect).h;
    }
  }

  [[nodiscard]]
  float GetCenterX() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      return r.x + (r.w / 2);
    } else {
      auto& r = std::get<FloatRect>(rect);
      return r.x + (r.w / 2.0f);
    }
  }

  [[nodiscard]]
  float GetCenterY() const noexcept {
    if constexpr (std::is_integral_v<T>) {
      auto& r = std::get<IntRect>(rect);
      return r.y + (r.y / 2);
    } else {
      auto& r = std::get<FloatRect>(rect);
      return r.y + (r.y / 2.0f);
    }
  }

  /**
   * Returns the maximum x-coordinate of the rectangle.
   *
   * @return the maximum x-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]]
  float GetMaxX() const noexcept{
    return GetX() + GetWidth();
  }

  /**
   * Returns the maximum y-coordinate of the rectangle.
   *
   * @return the maximum y-coordinate.
   * @since 0.1.0
   */
  [[nodiscard]]
  float GetMaxY() const noexcept {
    return GetY() + GetHeight();
  }

//  explicit operator Rectangle() const noexcept;

//  explicit operator SDL_Rect() const noexcept;
//
//  operator SDL_FRect() const noexcept;
};

}
