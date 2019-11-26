#include "abstract_entity.h"
#include "objects.h"
#include "movable_delegate.h"

namespace albinjohansson::wanderer {

AbstractEntity::AbstractEntity(Image_sptr sheet) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  movable = MovableObjectDelegate::Create(SIZE, SIZE);
}

AbstractEntity::~AbstractEntity() = default;

void AbstractEntity::Hurt(int dmg) noexcept {
  health -= dmg;
  if (health < 0) {
    health = 0;
  }
}

}
