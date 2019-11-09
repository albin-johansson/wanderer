#pragma once
#include "entity.h"

namespace wanderer::core {

/**
 * The Player class represents the entity that is controlled by the player.
 *
 * @see IEntity
 * @since 0.1.0
 */
class Player final : public IEntity {
 private:
  IMovableObject_uptr movableObject = nullptr;

 public:
  Player();

  ~Player() override = default;

  void Tick(float delta) override;

  void Draw(view::Renderer& renderer) const noexcept override;

  inline void Move(Direction direction) noexcept override {
    movableObject->Move(direction);
  }

  inline void Stop(Direction direction) noexcept override {
    movableObject->Stop(direction);
  }

  inline void Stop() noexcept override {
    movableObject->Stop();
  }

  inline void SavePosition() noexcept override {
    movableObject->SavePosition();
  }

  inline void Interpolate(float alpha) noexcept override {
    movableObject->Interpolate(alpha);
  }

  inline void SetSpeed(float speed) noexcept override {
    movableObject->SetSpeed(speed);
  }

  inline Vector2 GetVelocity() const noexcept override {
    return movableObject->GetVelocity();
  }

  inline Vector2 GetPosition() const noexcept override {
    return movableObject->GetPosition();
  }

  inline Vector2 GetPreviousPosition() const noexcept override {
    return movableObject->GetPreviousPosition();
  }

  inline float GetX() const noexcept override {
    return movableObject->GetX();
  }

  inline float GetY() const noexcept override {
    return movableObject->GetY();
  }

  inline int GetWidth() const noexcept override {
    return movableObject->GetWidth();
  }

  inline int GetHeight() const noexcept override {
    return movableObject->GetHeight();
  }

  inline Rectangle GetHitbox() const noexcept override {
    return movableObject->GetHitbox();
  }
};

}
