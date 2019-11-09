#pragma once
#include "direction.h"
#include "tickable.h"
#include "vector_2.h"
#include <memory>

namespace wanderer::core {

class IMovable : public ITickable {
 protected:
  IMovable() = default;

 public:
  ~IMovable() override = default;

  virtual void Move(Direction direction) noexcept = 0;

  virtual void Stop(Direction direction) noexcept = 0;

  virtual void Stop() noexcept = 0;

  virtual void SavePosition() noexcept = 0;

  virtual void Interpolate(float alpha) noexcept = 0;

  virtual void SetSpeed(float speed) noexcept = 0;

  virtual Vector2 GetVelocity() const noexcept = 0;

  virtual Vector2 GetPosition() const noexcept = 0;

  virtual Vector2 GetPreviousPosition() const noexcept = 0;
};

using IMovable_uptr = std::unique_ptr<IMovable>;
using IMovable_sptr = std::shared_ptr<IMovable>;
using IMovable_wptr = std::weak_ptr<IMovable>;

}