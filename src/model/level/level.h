#pragma once
#include <memory>

namespace wanderer::model {

/**
 * The ILevel class is an interface that specifies objects that represent different kind of levels
 * contained in the game world, such as houses and dungeons.
 *
 * \since 0.1.0
 */
class ILevel {
 protected:
  ILevel() = default;

 public:
  virtual ~ILevel() = default;

  /**
   * Updates the state of the level.
   *
   * \param delta the delta time that will be used.
   * \since 0.1.0
   */
  virtual void Update(double delta) = 0;

  // TODO edit level contents, queries about level state
};

using ILevel_uptr = std::unique_ptr<ILevel>;
using ILevel_sptr = std::shared_ptr<ILevel>;

} // namespace wanderer::model