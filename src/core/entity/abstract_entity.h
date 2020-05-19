#pragma once
#include <texture.h>

#include <memory>
#include <type_traits>

#include "animation.h"
#include "entity.h"
#include "hitbox.h"
#include "render_depth.h"
#include "wanderer_stdinc.h"

namespace albinjohansson::wanderer {

class IWandererCore;

/**
 * The AbstractEntity class is an abstract class that implements the IEntity
 * interface.
 *
 * @see IEntity
 * @since 0.1.0
 */
class AbstractEntity : public virtual IEntity {
 private:
  static constexpr int DEPTH =
      RenderDepth::range / 2;  // TODO maybe move to IEntity

  UniquePtr<IMovableObject> movable = nullptr;
  SharedPtr<ctn::Texture> sheet = nullptr;
  Animation animation;
  int health = 100;  // FIXME hard-coded

 protected:
  /**
   * @param sheet a pointer to the associated sprite sheet.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit AbstractEntity(const SharedPtr<ctn::Texture>& sheet);

 public:
  ~AbstractEntity() override;

  void tick(IWandererCore& core, float delta) override;

  void update_animation() noexcept override;

  void set_animation_frame(int index) noexcept override;

  void set_animation_frame_amount(int nFrames) override;

  void set_animation_delay(uint32 ms) override;

  void hurt(int dmg) noexcept override;

  void move(Direction direction) noexcept override;

  void stop(Direction direction) noexcept override;

  void stop() noexcept override;

  void interpolate(float alpha) noexcept override;

  void add_hitbox(const ctn::FRect& rectangle, const Vector2& offset) override;

  void add_x(float dx) noexcept override;

  void add_y(float dy) noexcept override;

  void set_x(float x) noexcept override;

  void set_y(float y) noexcept override;

  void set_speed(float speed) noexcept override;

  void set_velocity(const Vector2& velocity) noexcept override;

  void set_blocked(bool blocked) noexcept override;

  [[nodiscard]] float get_speed() const noexcept override;

  [[nodiscard]] int get_animation_frame() const noexcept override;

  [[nodiscard]] bool is_animation_done() const noexcept override;

  [[nodiscard]] ctn::Texture& get_sprite_sheet()
      const noexcept override;  // TODO make const

  [[nodiscard]] int get_health() const noexcept override;

  [[nodiscard]] bool is_dead() const noexcept override;

  [[nodiscard]] bool will_intersect(const IGameObject* other,
                                    float delta) const override;

  [[nodiscard]] Direction get_dominant_direction() const noexcept override;

  [[nodiscard]] const Vector2& get_previous_position() const noexcept override;

  [[nodiscard]] const Vector2& get_velocity() const noexcept override;

  [[nodiscard]] const Vector2& get_position() const noexcept override;

  [[nodiscard]] const Vector2& get_interpolated_position()
      const noexcept override;

  [[nodiscard]] Vector2 get_next_position(float delta) const noexcept override;

  [[nodiscard]] float get_x() const noexcept override;

  [[nodiscard]] float get_y() const noexcept override;

  [[nodiscard]] float get_width() const noexcept override;

  [[nodiscard]] float get_height() const noexcept override;

  [[nodiscard]] const Hitbox& get_hitbox() const noexcept override;

  [[nodiscard]] float get_center_y() const noexcept override;

  [[nodiscard]] int get_depth() const noexcept override;

  [[nodiscard]] uint64 get_unique_id() const noexcept override;
};

static_assert(std::has_virtual_destructor_v<AbstractEntity>);

}  // namespace albinjohansson::wanderer