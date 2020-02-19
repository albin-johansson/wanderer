#pragma once
#include <rectangle.h>

#include <memory>
#include <vector>

namespace albinjohansson::wanderer {

class IEntity;

/**
 * The EntityManager class is responsible for managing what entities should be
 * updated based on their position relative to the viewport.
 *
 * @since 0.1.0
 */
class EntityManager final {
 private:
  static constexpr int calcEntitiesThreshold = 100;

  std::vector<std::shared_ptr<IEntity>> entities;
  std::vector<IEntity*> closeEntities;

  int nTicksSinceUpdate = 0;
  bool firstTick = true;

  /**
   * Calculates all of the entities that intersect the supplied bounds.
   *
   * @param bounds the viewport bounds.
   * @since 0.1.0
   */
  void calculate_close_entities(const centurion::math::FRect& bounds);

 public:
  EntityManager();

  ~EntityManager();

  /**
   * Updates the state of the entity manager. The entity manager will update the
   * list of close entities within a certain interval of updates.
   *
   * @param bounds the viewport bounds.
   * @since 0.1.0
   * @see EntityManager::calcEntitiesThreshold
   */
  void update(const centurion::math::FRect& bounds);

  /**
   * Adds an entity to the entity manager.
   *
   * @param entity the entity that will be added, a null pointer will be
   * silently ignored.
   * @since 0.1.0
   */
  void add_entity(const std::shared_ptr<IEntity>& entity);

  /**
   * Returns all of the close entities.
   *
   * @return all of the close entities.
   * @since 0.1.0
   */
  [[nodiscard]] const std::vector<IEntity*>& get_close_entities() const;
};

}  // namespace albinjohansson::wanderer
