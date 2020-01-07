#include "spawnpoint.h"

namespace albinjohansson::wanderer {

Spawnpoint::Spawnpoint(EntityID id, const Vector2& position) noexcept
    : entity_id{id}, position{position} {}

Spawnpoint::~Spawnpoint() noexcept = default;

EntityID Spawnpoint::get_entity_id() const noexcept {
  return entity_id;
}

const Vector2& Spawnpoint::get_position() const noexcept {
  return position;
}

}
