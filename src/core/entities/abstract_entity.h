#pragma once
#include "entity.h"
#include "wanderer_core.h"
#include "animation.h"
#include "image.h"
#include "render_depth.h"

namespace albinjohansson::wanderer {

/**
 * The AbstractEntity class is an abstract class that implements the IEntity interface.
 *
 * @see IEntity
 * @since 0.1.0
 */
class AbstractEntity : public virtual IEntity {
 private:
  static constexpr int DEPTH = RenderDepth::RANGE / 2;

  IMovableObject_uptr movable = nullptr;
  Image_sptr sheet = nullptr;
  Animation animation;
  int health = 100;

 protected:
  /**
   * @param sheet a shared pointer to the associated sprite sheet.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit AbstractEntity(Image_sptr sheet);

 public:
  ~AbstractEntity() override;

  void Tick(IWandererCore& core, float delta) override { movable->Tick(core, delta); }

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

  [[nodiscard]] Image& GetSpriteSheet() const noexcept override { return *sheet; }

  [[nodiscard]] float GetX() const noexcept override { return movable->GetX(); }

  [[nodiscard]] float GetY() const noexcept override { return movable->GetY(); }

  [[nodiscard]] float GetCenterY() const noexcept override { return movable->GetCenterY(); }

  [[nodiscard]] int GetDepth() const noexcept final { return DEPTH; }

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
