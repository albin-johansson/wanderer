#include "entity_manager.h"

#include <rect.h>

#include "entity.h"
#include "hitbox.h"

using namespace centurion;

namespace wanderer {

EntityManager::EntityManager()
{
  m_entities.reserve(10);
  m_closeEntities.reserve(10);
}

EntityManager::~EntityManager() = default;

void EntityManager::calculate_close_entities(const FRect& bounds)
{
  m_closeEntities.clear();

  for (const auto& entity : m_entities) {
    if (entity->get_hitbox().intersects(bounds)) {
      m_closeEntities.push_back(entity.get());
    }
  }

  m_nTicksSinceUpdate = 0;
}

void EntityManager::update(const FRect& bounds)
{
  if (m_firstTick) {
    calculate_close_entities(bounds);
    m_firstTick = false;
    return;
  }

  ++m_nTicksSinceUpdate;

  if (m_nTicksSinceUpdate >= s_calcEntitiesThreshold) {
    calculate_close_entities(bounds);
  }
}

void EntityManager::add_entity(const SharedPtr<IEntity>& entity)
{
  if (entity) {
    m_entities.push_back(entity);
  }
}

const std::vector<IEntity*>& EntityManager::get_close_entities() const
{
  return m_closeEntities;
}

}  // namespace wanderer
