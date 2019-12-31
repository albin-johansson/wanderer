#pragma once
#include <vector>
#include <memory>

namespace albinjohansson::wanderer {

class IEntity;
class FRectangle;

/**
 * The EntityManager class is responsible for managing what entities should be updated based on
 * their position relative to the viewport.
 *
 * @since 0.1.0
 */
class EntityManager final {
 private:
  std::vector<std::shared_ptr<IEntity>> entities;
  std::vector<IEntity*> closeEntities;

  static constexpr int CALC_ENTITIES_THRESHOLD = 100;
  int nTicksSinceUpdate = 0;
  bool firstTick = true;

  /**
   * Calculates all of the entities that intersect the supplied bounds.
   *
   * @param bounds the viewport bounds.
   * @since 0.1.0
   */
  void CalculateCloseEntities(const FRectangle& bounds);

 public:
  EntityManager();

  ~EntityManager();

  /**
   * Updates the state of the entity manager. The entity manager will update the list of close
   * entities within a certain interval of updates.
   *
   * @param bounds the viewport bounds.
   * @since 0.1.0
   * @see EntityManager::CALC_ENTITIES_THRESHOLD
   */
  void Update(const FRectangle& bounds);

  /**
   * Adds an entity to the entity manager.
   *
   * @param entity the entity that will be added, a null pointer will be silently ignored.
   * @since 0.1.0
   */
  void AddEntity(const std::shared_ptr<IEntity>& entity);

  /**
   * Returns all of the close entities.
   *
   * @return all of the close entities.
   * @since 0.1.0
   */
  [[nodiscard]]
  const std::vector<IEntity*>& GetCloseEntities() const;
};

}
