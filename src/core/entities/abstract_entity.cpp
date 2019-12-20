#include "abstract_entity.h"
#include "image.h"
#include "objects.h"
#include "movable_delegate.h"
#include "hitbox.h"

namespace albinjohansson::wanderer {

AbstractEntity::AbstractEntity(const std::shared_ptr<Image>& sheet) {
  this->sheet = Objects::RequireNonNull(sheet);
  movable = std::make_unique<MovableDelegate>(DEPTH, SIZE, SIZE);
  movable->AddHitbox(Rectangle(movable->GetX(),
                               movable->GetY(),
                               movable->GetWidth(),
                               movable->GetHeight()), Vector2(0, 0));
}

AbstractEntity::~AbstractEntity() = default;

void AbstractEntity::Tick(IWandererCore& core, float delta) {
  movable->Tick(core, delta);
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

void AbstractEntity::Move(Direction direction) noexcept {
  movable->Move(direction);
}

void AbstractEntity::Stop(Direction direction) noexcept {
  movable->Stop(direction);
}

void AbstractEntity::Stop() noexcept {
  movable->Stop();
}

void AbstractEntity::Interpolate(float alpha) noexcept {
  movable->Interpolate(alpha);
}

void AbstractEntity::AddX(float dx) noexcept {
  movable->AddX(dx);
}

void AbstractEntity::AddY(float dy) noexcept {
  movable->AddY(dy);
}

void AbstractEntity::SetX(float x) noexcept {
  movable->SetX(x);
}

void AbstractEntity::SetY(float y) noexcept {
  movable->SetY(y);
}

void AbstractEntity::SetSpeed(float speed) noexcept {
  movable->SetSpeed(speed);
}

void AbstractEntity::SetVelocity(const Vector2& velocity) noexcept {
  movable->SetVelocity(velocity);
}

void AbstractEntity::AddHitbox(const Rectangle& rectangle, const Vector2& offset) {
  movable->AddHitbox(rectangle, offset);
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

float AbstractEntity::GetSpeed() const noexcept {
  return movable->GetSpeed();
}

Image& AbstractEntity::GetSpriteSheet() const noexcept {
  return *sheet;
}

Direction AbstractEntity::GetDominantDirection() const noexcept {
  return movable->GetDominantDirection();
}

Vector2 AbstractEntity::GetVelocity() const noexcept {
  return movable->GetVelocity();
}

Vector2 AbstractEntity::GetPosition() const noexcept {
  return movable->GetPosition();
}

Vector2 AbstractEntity::GetInterpolatedPosition() const noexcept {
  return movable->GetInterpolatedPosition();
}

float AbstractEntity::GetX() const noexcept {
  return movable->GetX();
}

float AbstractEntity::GetY() const noexcept {
  return movable->GetY();
}

float AbstractEntity::GetWidth() const noexcept {
  return movable->GetWidth();
}

float AbstractEntity::GetHeight() const noexcept {
  return movable->GetHeight();
}

const Hitbox& AbstractEntity::GetHitbox() const noexcept {
  return movable->GetHitbox();
}

float AbstractEntity::GetCenterY() const noexcept {
  return movable->GetCenterY();
}

int AbstractEntity::GetDepth() const noexcept {
  return movable->GetDepth();
}

bool AbstractEntity::IsBlocking() const noexcept {
  return movable->IsBlocking();
}

const Vector2& AbstractEntity::GetPreviousPosition() const noexcept {
  return movable->GetPreviousPosition();
}

bool AbstractEntity::WillIntersect(const IGameObject* other, float delta) const {
  return movable->WillIntersect(other, delta);
}

uint64_t AbstractEntity::GetUniqueID() const noexcept {
  return movable->GetUniqueID();
}

Vector2 AbstractEntity::GetNextPosition(float delta) const noexcept {
  return movable->GetNextPosition(delta);
}

}
