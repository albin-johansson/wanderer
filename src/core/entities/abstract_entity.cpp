#include "abstract_entity.h"
#include "image.h"
#include "require.h"
#include "movable_delegate.h"
#include "hitbox.h"

namespace albinjohansson::wanderer {

AbstractEntity::AbstractEntity(const std::shared_ptr<Image>& sheet) {
  this->sheet = Require::NotNull(sheet);
  movable = std::make_unique<MovableDelegate>(DEPTH, SIZE, SIZE);
  movable->add_hitbox(FRectangle{movable->get_x(),
                                 movable->get_y(),
                                 Area{movable->get_width(), movable->get_height()}},
                      Vector2{});
  movable->set_blocked(true);
}

AbstractEntity::~AbstractEntity() = default;

void AbstractEntity::tick(IWandererCore& core, float delta) {
  movable->tick(core, delta);
}

void AbstractEntity::UpdateAnimation() noexcept {
  animation.Update();
}

void AbstractEntity::SetAnimationFrame(int index) noexcept {
  animation.SetFrame(index);
}

void AbstractEntity::SetAnimationFrameAmount(int nFrames) {
  animation.SetNumberOfFrames(nFrames);
}

void AbstractEntity::SetAnimationDelay(uint32_t ms) {
  animation.SetDelay(ms);
}

void AbstractEntity::Hurt(int dmg) noexcept {
  health -= dmg;
  if (health < 0) {
    health = 0;
  }
}

void AbstractEntity::move(Direction direction) noexcept {
  movable->move(direction);
}

void AbstractEntity::stop(Direction direction) noexcept {
  movable->stop(direction);
}

void AbstractEntity::stop() noexcept {
  movable->stop();
}

void AbstractEntity::interpolate(float alpha) noexcept {
  movable->interpolate(alpha);
}

void AbstractEntity::add_x(float dx) noexcept {
  movable->add_x(dx);
}

void AbstractEntity::add_y(float dy) noexcept {
  movable->add_y(dy);
}

void AbstractEntity::set_x(float x) noexcept {
  movable->set_x(x);
}

void AbstractEntity::set_y(float y) noexcept {
  movable->set_y(y);
}

void AbstractEntity::set_speed(float speed) noexcept {
  movable->set_speed(speed);
}

void AbstractEntity::set_velocity(const Vector2& velocity) noexcept {
  movable->set_velocity(velocity);
}

void AbstractEntity::add_hitbox(const FRectangle& rectangle, const Vector2& offset) {
  movable->add_hitbox(rectangle, offset);
}

void AbstractEntity::set_blocked(bool blocked) noexcept {
  movable->set_blocked(blocked);
}

int AbstractEntity::GetAnimationFrame() const noexcept {
  return animation.GetIndex();
}

bool AbstractEntity::IsAnimationDone() const noexcept {
  return animation.IsDone();
}

int AbstractEntity::GetHealth() const noexcept {
  return health;
}

bool AbstractEntity::IsDead() const noexcept {
  return health <= 0;
}

float AbstractEntity::get_speed() const noexcept {
  return movable->get_speed();
}

Image& AbstractEntity::GetSpriteSheet() const noexcept {
  return *sheet;
}

Direction AbstractEntity::get_dominant_direction() const noexcept {
  return movable->get_dominant_direction();
}

const Vector2& AbstractEntity::get_velocity() const noexcept {
  return movable->get_velocity();
}

const Vector2& AbstractEntity::get_position() const noexcept {
  return movable->get_position();
}

const Vector2& AbstractEntity::get_interpolated_position() const noexcept {
  return movable->get_interpolated_position();
}

float AbstractEntity::get_x() const noexcept {
  return movable->get_x();
}

float AbstractEntity::get_y() const noexcept {
  return movable->get_y();
}

float AbstractEntity::get_width() const noexcept {
  return movable->get_width();
}

float AbstractEntity::get_height() const noexcept {
  return movable->get_height();
}

const Hitbox& AbstractEntity::get_hitbox() const noexcept {
  return movable->get_hitbox();
}

float AbstractEntity::GetCenterY() const noexcept {
  return movable->GetCenterY();
}

int AbstractEntity::GetDepth() const noexcept {
  return movable->GetDepth();
}

const Vector2& AbstractEntity::get_previous_position() const noexcept {
  return movable->get_previous_position();
}

bool AbstractEntity::will_intersect(const IGameObject* other, float delta) const {
  return movable->will_intersect(other, delta);
}

uint64_t AbstractEntity::get_unique_id() const noexcept {
  return movable->get_unique_id();
}

Vector2 AbstractEntity::get_next_position(float delta) const noexcept {
  return movable->get_next_position(delta);
}

}
