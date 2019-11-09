#pragma once
#include "drawable.h"
#include "rectangle.h"
#include <memory>

namespace wanderer::core {

class IGameObject : public IDrawable {
 protected:
  IGameObject() = default;

 public:
  ~IGameObject() override = default;

  virtual float GetX() const noexcept = 0;

  virtual float GetY() const noexcept = 0;

  virtual int GetWidth() const noexcept = 0;

  virtual int GetHeight() const noexcept = 0;

  virtual Rectangle GetHitbox() const noexcept = 0;
};

using IGameObject_uptr = std::unique_ptr<IGameObject>;
using IGameObject_sptr = std::shared_ptr<IGameObject>;
using IGameObject_wptr = std::weak_ptr<IGameObject>;

}