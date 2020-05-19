#include "abstract_entity.h"

#include "movable_delegate.h"
#include "require.h"

using namespace centurion;

;

namespace wanderer {

AbstractEntity::AbstractEntity(const SharedPtr<Texture>& sheet)
{
  this->m_sheet = Require::not_null(sheet);
  m_movable = std::make_unique<MovableDelegate>(
      s_depth, GameConstants::entity_width, GameConstants::entity_height);
  m_movable->add_hitbox(FRect{m_movable->get_x(),
                              m_movable->get_y(),
                              m_movable->get_width(),
                              m_movable->get_height()},
                        Vector2{});
  m_movable->set_blocked(true);
}

AbstractEntity::~AbstractEntity() = default;

void AbstractEntity::tick(IWandererCore& core, float delta)
{
  m_movable->tick(core, delta);
}

void AbstractEntity::update_animation() noexcept
{
  m_animation.update();
}

void AbstractEntity::set_animation_frame(int index) noexcept
{
  m_animation.set_frame(index);
}

void AbstractEntity::set_animation_frame_amount(int nFrames)
{
  m_animation.set_number_of_frames(nFrames);
}

void AbstractEntity::set_animation_delay(uint32_t ms)
{
  m_animation.set_delay(ms);
}

void AbstractEntity::hurt(int dmg) noexcept
{
  m_health -= dmg;
  if (m_health < 0) {
    m_health = 0;
  }
}

void AbstractEntity::move(Direction direction) noexcept
{
  m_movable->move(direction);
}

void AbstractEntity::stop(Direction direction) noexcept
{
  m_movable->stop(direction);
}

void AbstractEntity::stop() noexcept
{
  m_movable->stop();
}

void AbstractEntity::interpolate(float alpha) noexcept
{
  m_movable->interpolate(alpha);
}

void AbstractEntity::add_x(float dx) noexcept
{
  m_movable->add_x(dx);
}

void AbstractEntity::add_y(float dy) noexcept
{
  m_movable->add_y(dy);
}

void AbstractEntity::set_x(float x) noexcept
{
  m_movable->set_x(x);
}

void AbstractEntity::set_y(float y) noexcept
{
  m_movable->set_y(y);
}

void AbstractEntity::set_speed(float speed) noexcept
{
  m_movable->set_speed(speed);
}

void AbstractEntity::set_velocity(const Vector2& velocity) noexcept
{
  m_movable->set_velocity(velocity);
}

void AbstractEntity::add_hitbox(const FRect& rectangle, const Vector2& offset)
{
  m_movable->add_hitbox(rectangle, offset);
}

void AbstractEntity::set_blocked(bool blocked) noexcept
{
  m_movable->set_blocked(blocked);
}

int AbstractEntity::get_animation_frame() const noexcept
{
  return m_animation.get_index();
}

bool AbstractEntity::is_animation_done() const noexcept
{
  return m_animation.is_done();
}

int AbstractEntity::get_health() const noexcept
{
  return m_health;
}

bool AbstractEntity::is_dead() const noexcept
{
  return m_health <= 0;
}

float AbstractEntity::get_speed() const noexcept
{
  return m_movable->get_speed();
}

Texture& AbstractEntity::get_sprite_sheet() const noexcept
{
  return *m_sheet;
}

Direction AbstractEntity::get_dominant_direction() const noexcept
{
  return m_movable->get_dominant_direction();
}

const Vector2& AbstractEntity::get_velocity() const noexcept
{
  return m_movable->get_velocity();
}

const Vector2& AbstractEntity::get_position() const noexcept
{
  return m_movable->get_position();
}

const Vector2& AbstractEntity::get_interpolated_position() const noexcept
{
  return m_movable->get_interpolated_position();
}

float AbstractEntity::get_x() const noexcept
{
  return m_movable->get_x();
}

float AbstractEntity::get_y() const noexcept
{
  return m_movable->get_y();
}

float AbstractEntity::get_width() const noexcept
{
  return m_movable->get_width();
}

float AbstractEntity::get_height() const noexcept
{
  return m_movable->get_height();
}

const Hitbox& AbstractEntity::get_hitbox() const noexcept
{
  return m_movable->get_hitbox();
}

float AbstractEntity::get_center_y() const noexcept
{
  return m_movable->get_center_y();
}

int AbstractEntity::get_depth() const noexcept
{
  return m_movable->get_depth();
}

const Vector2& AbstractEntity::get_previous_position() const noexcept
{
  return m_movable->get_previous_position();
}

bool AbstractEntity::will_intersect(const IGameObject* other, float delta) const
{
  return m_movable->will_intersect(other, delta);
}

uint64_t AbstractEntity::get_unique_id() const noexcept
{
  return m_movable->get_unique_id();
}

Vector2 AbstractEntity::get_next_position(float delta) const noexcept
{
  return m_movable->get_next_position(delta);
}

}  // namespace wanderer
