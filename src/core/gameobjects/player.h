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

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override;

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

  [[nodiscard]] inline Vector2 GetVelocity() const noexcept override {
    return movableObject->GetVelocity();
  }

  [[nodiscard]] inline Vector2 GetPosition() const noexcept override {
    return movableObject->GetPosition();
  }

  [[nodiscard]] inline Vector2 GetInterpolatedPosition() const noexcept override {
    return movableObject->GetInterpolatedPosition();
  }

  [[nodiscard]] inline float GetX() const noexcept override {
    return movableObject->GetX();
  }

  [[nodiscard]] inline float GetY() const noexcept override {
    return movableObject->GetY();
  }

  [[nodiscard]] inline int GetWidth() const noexcept override {
    return movableObject->GetWidth();
  }

  [[nodiscard]] inline int GetHeight() const noexcept override {
    return movableObject->GetHeight();
  }

  [[nodiscard]] inline Rectangle GetHitbox() const noexcept override {
    return movableObject->GetHitbox();
  }
};

}
