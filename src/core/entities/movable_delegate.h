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
  float speed = 0;
  const int depth;
  const float width;
  const float height;
  Direction dominantDirection = Direction::Down;
  uint64_t uniqueId = 0;

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

  void Draw(const Renderer& renderer, const Viewport& viewport) const noexcept override;

  void tick(IWandererCore& core, float delta) override;

  void move(Direction direction) noexcept override;

  void stop(Direction direction) noexcept override;

  void stop() noexcept override;

  void interpolate(float alpha) noexcept override;

  void add_x(float dx) noexcept override;

  void add_y(float dy) noexcept override;

  void set_x(float x) noexcept override;

  void set_y(float y) noexcept override;

  void set_speed(float speed) noexcept override;

  void set_velocity(const Vector2& v) noexcept override;

  void set_blocked(bool blocked) noexcept override;

  void add_hitbox(const FRectangle& rectangle, const Vector2& offset) override;

  [[nodiscard]]
  int GetDepth() const noexcept override;

  [[nodiscard]]
  float get_speed() const noexcept override;

  [[nodiscard]]
  float get_x() const noexcept override;

  [[nodiscard]]
  float get_y() const noexcept override;

  [[nodiscard]]
  float GetCenterY() const noexcept override;

  [[nodiscard]]
  float get_width() const noexcept override;

  [[nodiscard]]
  float get_height() const noexcept override;

  [[nodiscard]]
  const Hitbox& get_hitbox() const noexcept override;

  [[nodiscard]]
  bool will_intersect(const IGameObject* other, float delta) const override;

  [[nodiscard]]
  Direction get_dominant_direction() const noexcept override;

  [[nodiscard]]
  const Vector2& get_previous_position() const noexcept override;

  [[nodiscard]]
  const Vector2& get_velocity() const noexcept override;

  [[nodiscard]]
  const Vector2& get_position() const noexcept override;

  [[nodiscard]]
  const Vector2& get_interpolated_position() const noexcept override;

  [[nodiscard]]
  uint64_t get_unique_id() const noexcept override;

  [[nodiscard]]
  Vector2 get_next_position(float delta) const noexcept override;

};

}
