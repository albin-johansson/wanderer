#pragma once
#include "entity.h"
#include "animation.h"
#include "image.h"

namespace wanderer::core {

class AbstractEntity : public IEntity {
 private:
  IMovableObject_uptr movable = nullptr;
  visuals::Image_sptr sheet = nullptr;
  visuals::Animation animation;
  int health = 100;

 public:
  explicit AbstractEntity(visuals::Image_sptr sheet);

  ~AbstractEntity() override;

  void Tick(const IGame& game, float delta) override { movable->Tick(game, delta); }

  void Move(Direction direction) noexcept override { movable->Move(direction); }

  void Stop(Direction direction) noexcept override { movable->Stop(direction); }

  void Stop() noexcept override { movable->Stop(); }

  void SavePosition() noexcept override { movable->SavePosition(); }

  void Interpolate(float alpha) noexcept override { movable->Interpolate(alpha); }

  void AddX(float dx) noexcept override { movable->AddX(dx); }

  void AddY(float dy) noexcept override { movable->AddY(dy); }

  void SetX(float x) noexcept override { movable->SetX(x); }

  void SetY(float y) noexcept override { movable->SetY(y); }

  void SetSpeed(float speed) noexcept override { movable->SetSpeed(speed); }

  void SetVelocity(const Vector2& v) noexcept override { movable->SetVelocity(v); }

  [[nodiscard]] float GetSpeed() const noexcept override { return movable->GetSpeed(); }

  [[nodiscard]] Direction GetDominantDirection() const noexcept override {
    return movable->GetDominantDirection();
  }

  [[nodiscard]] Vector2 GetVelocity() const noexcept override {
    return movable->GetVelocity();
  }

  [[nodiscard]] Vector2 GetPosition() const noexcept override {
    return movable->GetPosition();
  }

  [[nodiscard]] Vector2 GetInterpolatedPosition() const noexcept override {
    return movable->GetInterpolatedPosition();
  }

  [[nodiscard]] visuals::Image& GetSpriteSheet() const noexcept override { return *sheet; }

  [[nodiscard]] float GetX() const noexcept override { return movable->GetX(); }

  [[nodiscard]] float GetY() const noexcept override { return movable->GetY(); }

  [[nodiscard]] float GetWidth() const noexcept override { return movable->GetWidth(); }

  [[nodiscard]] float GetHeight() const noexcept override { return movable->GetHeight(); }

  [[nodiscard]] Rectangle GetHitbox() const noexcept override { return movable->GetHitbox(); }

  void UpdateAnimation() noexcept override { animation.Update(); }

  void SetAnimationFrame(int index) noexcept override { animation.SetFrame(index); }

  void SetAnimationFrameAmount(int nFrames) override { animation.SetNumberOfFrames(nFrames); }

  void SetAnimationDelay(Uint32 ms) override { animation.SetDelay(ms); }

  [[nodiscard]] int GetAnimationFrame() const noexcept override { return animation.GetIndex(); }

  [[nodiscard]] bool IsAnimationDone() const noexcept override { return animation.IsDone(); }

  void Hurt(int dmg) noexcept override;

  [[nodiscard]] int GetHealth() const noexcept override { return health; }

  [[nodiscard]] bool IsDead() const noexcept override { return health <= 0; }
};

}
