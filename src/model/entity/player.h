#pragma once
#include "vector_2.h"
#include "direction.h"
#include <memory>

namespace wanderer::model {

class Player final {
 private:
  static constexpr int MOV_SPEED = 12;
  static constexpr double SQRT_TWO = 1.41421356;

  Vector2 position;
  Vector2 speed;
  const int width;
  const int height;

 public:
  Player(int x, int y, int width, int height) : width(width), height(height) {
    position.SetX(x);
    position.SetY(y);
  }

  ~Player() = default;

  void Update(double delta);

  void Move(Direction direction);

  void Stop(Direction direction);

  [[nodiscard]] inline int GetX() const noexcept { return position.GetX(); }

  [[nodiscard]] inline int GetY() const noexcept { return position.GetY(); }

  [[nodiscard]] inline int GetWidth() const noexcept { return 100; }

  [[nodiscard]] inline int GetHeight() const noexcept { return 100; }

};

using Player_uptr = std::unique_ptr<Player>;
using Player_sptr = std::shared_ptr<Player>;
using Player_wptr = std::weak_ptr<Player>;

}