#pragma once
#include "entity.h"
#include "entity_state_machine.h"

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
  IEntityStateMachine_uptr entityStateMachine = nullptr;

 public:
  Player();

  ~Player() override = default;

  void HandleInput(const Input& input) override;

  void Tick(float delta) override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const noexcept override;

  void SetState(EntityStateID id) override;

  inline void AddX(float dx) noexcept override {
    movableObject->AddX(dx);
  }

  inline void AddY(float dy) noexcept override {
    movableObject->AddY(dy);
  }

  inline void SetX(float x) noexcept override {
    movableObject->SetX(x);
  }

  inline void SetY(float y) noexcept override {
    movableObject->SetY(y);
  }

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

  [[nodiscard]] inline float GetWidth() const noexcept override {
    return movableObject->GetWidth();
  }

  [[nodiscard]] inline float GetHeight() const noexcept override {
    return movableObject->GetHeight();
  }

  [[nodiscard]] inline Rectangle GetHitbox() const noexcept override {
    return movableObject->GetHitbox();
  }
};

}
