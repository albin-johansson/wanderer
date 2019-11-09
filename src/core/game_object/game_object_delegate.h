#pragma once
#include "game_object.h"
#include "vector_2.h"

namespace wanderer::core {

class GameObjectDelegate final : public IGameObject {
 private:
  Vector2 position;
  int width;
  int height;

 public:
  GameObjectDelegate() noexcept;

  ~GameObjectDelegate() noexcept override = default;

  void Draw(view::Renderer& renderer) const noexcept override { /* do nothing */ }

  inline float GetX() const noexcept override {
    return position.GetX();
  }

  inline float GetY() const noexcept override {
    return position.GetY();
  }

  inline int GetWidth() const noexcept override {
    return width;
  }

  inline int GetHeight() const noexcept override {
    return height;
  }

  inline Rectangle GetHitbox() const noexcept override {
    return Rectangle(position.GetX(), position.GetY(), width, height);
  }
};

}