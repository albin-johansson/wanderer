#include "abstract_entity.h"
#include "objects.h"
#include "movable_delegate.h"

namespace wanderer::core {

AbstractEntity::AbstractEntity(visuals::Image_sptr sheet) {
  this->sheet = Objects::RequireNonNull(std::move(sheet));
  movable = MovableObjectDelegate::Create(200, 200);
}

AbstractEntity::~AbstractEntity() = default;

void AbstractEntity::Hurt(int dmg) noexcept {
  health -= dmg;
  if (health < 0) {
    health = 0;
  }
}

}
