#include "spawnpoint.h"

namespace wanderer {

Spawnpoint::Spawnpoint(EntityID id, const Vector2& position) noexcept
    : m_entityId{id}, m_position{position}
{}

Spawnpoint::~Spawnpoint() noexcept = default;

EntityID Spawnpoint::get_entity_id() const noexcept
{
  return m_entityId;
}

const Vector2& Spawnpoint::get_position() const noexcept
{
  return m_position;
}

}  // namespace wanderer
