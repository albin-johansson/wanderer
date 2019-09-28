#pragma once
#include "level.h"
#include "player.h"
#include <vector>
#include <memory>

namespace wanderer::model {

/*
 *
 *               World
 *           ______|
 *           |
 *           v
 *         Level
 *           |
 *           v
 * Outside, Houses, etc.
 *
 *
 */
/**
 * The World class represents the entire game world and serves as a parent class for the levels,
 * mobs, items, etc.
 *
 * @since 0.1.0
 */
class World final {
 private:
  std::vector<ILevel_sptr> levels;
  ILevel_sptr activeLevel = nullptr;
  Player_sptr player = nullptr;

 public:
  World();

  ~World();

  /**
   * Updates the state of the world.
   *
   * @param delta the delta time that will be used.
   * @since 0.1.0
   */
  void Update(double delta);

  /**
   * Sets the active level.
   *
   * @param level a unique pointer to the level that will be used, may be nullptr.
   * @since 0.1.0
   */
  void SetLevel(ILevel_sptr level) noexcept;

  Player_sptr GetPlayer();

};

using World_uptr = std::unique_ptr<World>;

} // namespace wanderer::model