#include "entity_manager.h"
#include "entity.h"
#include "rectangle.h"
#include "hitbox.h"

namespace albinjohansson::wanderer {

EntityManager::EntityManager() {
  entities.reserve(10);
  closeEntities.reserve(10);
}

EntityManager::~EntityManager() = default;

void EntityManager::calculate_close_entities(const FRectangle& bounds) {
  closeEntities.clear();

  for (const auto& entity : entities) {
    if (entity->get_hitbox().intersects(bounds)) {
      closeEntities.push_back(entity.get());
    }
  }

  nTicksSinceUpdate = 0;
}

void EntityManager::update(const FRectangle& bounds) {
  if (firstTick) {
    calculate_close_entities(bounds);
    firstTick = false;
    return;
  }

  ++nTicksSinceUpdate;

  if (nTicksSinceUpdate >= calcEntitiesThreshold) {
    calculate_close_entities(bounds);
  }
}

void EntityManager::add_entity(const std::shared_ptr<IEntity>& entity) {
  if (entity) {
    entities.push_back(entity);
  }
}

const std::vector<IEntity*>& EntityManager::get_close_entities() const {
  return closeEntities;
}

}
