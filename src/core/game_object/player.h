#pragma once
#include "entity.h"

namespace wanderer::core {

class Player : public IEntity {
 private:
  IGameObject_uptr gameObject = nullptr;
  IMovable_uptr movable = nullptr;

 public:
  Player();

  ~Player() override = default;

  void Tick(float delta) override;

  void Draw(view::Renderer& renderer) const noexcept override;

  inline void Move(Direction direction) noexcept override {
    movable->Move(direction);
  }

  inline void Stop(Direction direction) noexcept override {
    movable->Stop(direction);
  }

  inline void Stop() noexcept override {
    movable->Stop();
  }

  inline void SavePosition() noexcept override {
    movable->SavePosition();
  }

  inline void Interpolate(float alpha) noexcept override {
    movable->Interpolate(alpha);
  }

  inline void SetSpeed(float speed) noexcept override {
    movable->SetSpeed(speed);
  }

  inline Vector2 GetVelocity() const noexcept override {
    return movable->GetVelocity();
  }

  inline Vector2 GetPosition() const noexcept override {
    return movable->GetPosition();
  }

  inline Vector2 GetPreviousPosition() const noexcept override {
    return movable->GetPreviousPosition();
  }

  inline float GetX() const noexcept override {
    return movable->GetPosition().GetX(); // FIXME wasteful
  }

  inline float GetY() const noexcept override {
    return movable->GetPosition().GetY();
  }

  inline int GetWidth() const noexcept override {
    return gameObject->GetWidth();
  }

  inline int GetHeight() const noexcept override {
    return gameObject->GetHeight();
  }

  inline Rectangle GetHitbox() const noexcept override {
    return gameObject->GetHitbox();
  }
};

}
