#include "entity_manager.h"
#include "entity.h"
#include "rectangle.h"

namespace albinjohansson::wanderer {

EntityManager::EntityManager() {
  entities.reserve(10);
  closeEntities.reserve(10);
}

EntityManager::~EntityManager() = default;

void EntityManager::CalculateCloseEntities(const FRectangle& bounds) {
  closeEntities.clear();

  for (const auto& entity : entities) {
    if (entity->GetHitbox().Intersects(bounds)) {
      closeEntities.push_back(entity.get());
    }
  }

  nTicksSinceUpdate = 0;
}

void EntityManager::Update(const FRectangle& bounds) {
  if (firstTick) {
    CalculateCloseEntities(bounds);
    firstTick = false;
    return;
  }

  ++nTicksSinceUpdate;

  if (nTicksSinceUpdate >= CALC_ENTITIES_THRESHOLD) {
    CalculateCloseEntities(bounds);
  }
}

void EntityManager::AddEntity(const std::shared_ptr<IEntity>& entity) {
  if (entity) {
    entities.push_back(entity);
  }
}

const std::vector<IEntity*>& EntityManager::GetCloseEntities() const {
  return closeEntities;
}

}
