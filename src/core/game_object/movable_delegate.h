#pragma once
#include "movable.h"
#include "vector_2.h"

namespace wanderer::core {

class MovableDelegate final : public IMovable {
 private:
  Vector2 velocity;
  Vector2 currPosition;
  Vector2 prevPosition;
  float speed = 0;

 public:
  MovableDelegate();

  ~MovableDelegate() override;

  void Tick(float delta) override;

  void Move(Direction direction) noexcept override;

  void Stop(Direction direction) noexcept override;

  void Stop() noexcept override;

  void SavePosition() noexcept override;

  void Interpolate(float alpha) noexcept override;

  void SetSpeed(float speed) noexcept override;

  Vector2 GetVelocity() const noexcept override;

  Vector2 GetPosition() const noexcept override;

  Vector2 GetPreviousPosition() const noexcept override;
};

}
