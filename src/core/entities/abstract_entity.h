#pragma once
#include "entity.h"
#include "animation.h"
#include "render_depth.h"
#include "hitbox.h"
#include <type_traits>

namespace albinjohansson::wanderer {

class IWandererCore;
class Image;

/**
 * The AbstractEntity class is an abstract class that implements the IEntity interface.
 *
 * @see IEntity
 * @since 0.1.0
 */
class AbstractEntity : public virtual IEntity {
 private:
  static constexpr int DEPTH = RenderDepth::RANGE / 2; // TODO maybe move to IEntity

  std::unique_ptr<IMovableObject> movable = nullptr;
  std::shared_ptr<Image> sheet = nullptr;
  Animation animation;
  int health = 100; // FIXME hard-coded

 protected:
  /**
   * @param sheet a pointer to the associated sprite sheet.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit AbstractEntity(const std::shared_ptr<Image>& sheet);

 public:
  ~AbstractEntity() override;

  void Tick(IWandererCore& core, float delta) override;

  void UpdateAnimation() noexcept override;

  void SetAnimationFrame(int index) noexcept override;

  void SetAnimationFrameAmount(int nFrames) override;

  void SetAnimationDelay(uint32_t ms) override;

  void Hurt(int dmg) noexcept override;

  void Move(Direction direction) noexcept override;

  void Stop(Direction direction) noexcept override;

  void Stop() noexcept override;

  void Interpolate(float alpha) noexcept override;

  void AddHitbox(const FRectangle& rectangle, const Vector2& offset) override;

  void AddX(float dx) noexcept override;

  void AddY(float dy) noexcept override;

  void SetX(float x) noexcept override;

  void SetY(float y) noexcept override;

  void SetSpeed(float speed) noexcept override;

  void SetVelocity(const Vector2& velocity) noexcept override;

  void SetBlocked(bool blocked) noexcept override;

  [[nodiscard]]
  float GetSpeed() const noexcept override;

  [[nodiscard]]
  int GetAnimationFrame() const noexcept override;

  [[nodiscard]]
  bool IsAnimationDone() const noexcept override;

  [[nodiscard]]
  Image& GetSpriteSheet() const noexcept override;

  [[nodiscard]]
  int GetHealth() const noexcept override;

  [[nodiscard]]
  bool IsDead() const noexcept override;

  [[nodiscard]]
  bool WillIntersect(const IGameObject* other, float delta) const override;

  [[nodiscard]]
  Direction GetDominantDirection() const noexcept override;

  [[nodiscard]]
  const Vector2& GetPreviousPosition() const noexcept override;

  [[nodiscard]]
  const Vector2& GetVelocity() const noexcept override;

  [[nodiscard]]
  const Vector2& GetPosition() const noexcept override;

  [[nodiscard]]
  const Vector2& GetInterpolatedPosition() const noexcept override;

  [[nodiscard]]
  Vector2 GetNextPosition(float delta) const noexcept override;

  [[nodiscard]]
  float GetX() const noexcept override;

  [[nodiscard]]
  float GetY() const noexcept override;

  [[nodiscard]]
  float GetWidth() const noexcept override;

  [[nodiscard]]
  float GetHeight() const noexcept override;

  [[nodiscard]]
  const Hitbox& GetHitbox() const noexcept override;

  [[nodiscard]]
  float GetCenterY() const noexcept override;

  [[nodiscard]]
  int GetDepth() const noexcept override;

  [[nodiscard]]
  uint64_t GetUniqueID() const noexcept override;
};

static_assert(std::has_virtual_destructor_v<AbstractEntity>);

}