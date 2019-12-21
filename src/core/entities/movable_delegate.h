#pragma once
#include "hitbox.h"
#include "movable_object.h"
#include "vector_2.h"

namespace albinjohansson::wanderer {

/**
 * The MovableDelegate class is an implementation of the IGameObject interface that is meant
 * to be used as a delegate.
 *
 * @see IMovableObject
 * @since 0.1.0
 */
class MovableDelegate final : public IMovableObject {
 private:
  Vector2 velocity;
  Vector2 currPosition;
  Vector2 prevPosition;
  Vector2 interpolatedPosition;
  Hitbox hitbox;
  uint64_t uniqueId = 0;
  Direction dominantDirection = Direction::DOWN;
  const int depth;
  const float width;
  const float height;
  float speed = 0;
  bool isBlocking = false;

  /**
   * Saves the position of the movable.
   *
   * @since 0.1.0
   */
  void SavePosition() noexcept;

  void UpdatePosition();

  /**
   * Updates the dominant direction.
   *
   * @since 0.1.0
   */
  void UpdateDirection();

 public:
  /**
   * @param depth the depth value of the object.
   * @param width the width of the object.
   * @param height the height of the object.
   * @throws std::invalid_argument if either of the supplied dimensions are less than one.
   * @since 0.1.0
   */
  MovableDelegate(int depth, float width, float height);

  ~MovableDelegate() override;

  void Draw(Renderer& renderer, const Viewport& viewport) const noexcept override;

  void Tick(IWandererCore& core, float delta) override;

  void Move(Direction direction) noexcept override;

  void Stop(Direction direction) noexcept override;

  void Stop() noexcept override;

  void Interpolate(float alpha) noexcept override;

  void AddX(float dx) noexcept override;

  void AddY(float dy) noexcept override;

  void SetX(float x) noexcept override;

  void SetY(float y) noexcept override;

  void SetSpeed(float speed) noexcept override;

  void SetVelocity(const Vector2& v) noexcept override;

  void SetBlocked(bool blocked) noexcept override;

  void AddHitbox(const Rectangle& rectangle, const Vector2& offset) override;

  [[nodiscard]] int GetDepth() const noexcept override;

  [[nodiscard]] float GetSpeed() const noexcept override;

  [[nodiscard]] float GetX() const noexcept override;

  [[nodiscard]] float GetY() const noexcept override;

  [[nodiscard]] float GetCenterY() const noexcept override;

  [[nodiscard]] float GetWidth() const noexcept override;

  [[nodiscard]] float GetHeight() const noexcept override;

  [[nodiscard]] const Hitbox& GetHitbox() const noexcept override;

  [[nodiscard]] bool WillIntersect(const IGameObject* other, float delta) const override;

  [[nodiscard]] Direction GetDominantDirection() const noexcept override;

  [[nodiscard]] const Vector2& GetPreviousPosition() const noexcept override;

  [[nodiscard]] Vector2 GetVelocity() const noexcept override;

  [[nodiscard]] Vector2 GetPosition() const noexcept override;

  [[nodiscard]] Vector2 GetInterpolatedPosition() const noexcept override;

  [[nodiscard]] uint64_t GetUniqueID() const noexcept override;

  [[nodiscard]] Vector2 GetNextPosition(float delta) const noexcept override;

};

}
