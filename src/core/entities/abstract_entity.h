#pragma once
#include "entity.h"
#include "animation.h"
#include "render_depth.h"
#include "hitbox.h"
#include <type_traits>
#include <memory>

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

  void tick(IWandererCore& core, float delta) override;

  void UpdateAnimation() noexcept override;

  void SetAnimationFrame(int index) noexcept override;

  void SetAnimationFrameAmount(int nFrames) override;

  void SetAnimationDelay(uint32_t ms) override;

  void Hurt(int dmg) noexcept override;

  void move(Direction direction) noexcept override;

  void stop(Direction direction) noexcept override;

  void stop() noexcept override;

  void interpolate(float alpha) noexcept override;

  void add_hitbox(const FRectangle& rectangle, const Vector2& offset) override;

  void add_x(float dx) noexcept override;

  void add_y(float dy) noexcept override;

  void set_x(float x) noexcept override;

  void set_y(float y) noexcept override;

  void set_speed(float speed) noexcept override;

  void set_velocity(const Vector2& velocity) noexcept override;

  void set_blocked(bool blocked) noexcept override;

  [[nodiscard]]
  float get_speed() const noexcept override;

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
  Vector2 get_next_position(float delta) const noexcept override;

  [[nodiscard]]
  float get_x() const noexcept override;

  [[nodiscard]]
  float get_y() const noexcept override;

  [[nodiscard]]
  float get_width() const noexcept override;

  [[nodiscard]]
  float get_height() const noexcept override;

  [[nodiscard]]
  const Hitbox& get_hitbox() const noexcept override;

  [[nodiscard]]
  float GetCenterY() const noexcept override;

  [[nodiscard]]
  int GetDepth() const noexcept override;

  [[nodiscard]]
  uint64_t get_unique_id() const noexcept override;
};

static_assert(std::has_virtual_destructor_v<AbstractEntity>);

}