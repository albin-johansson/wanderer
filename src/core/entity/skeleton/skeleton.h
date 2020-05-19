#pragma once
#include <memory>

#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "game_constants.h"
#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class Skeleton final : public AbstractEntity {
 private:
  UniquePtr<IEntityStateMachine> stateMachine = nullptr;

  void init();

 public:
  static constexpr float HOMING_RANGE = GameConstants::tile_size * 4.0f;

  explicit Skeleton(const SharedPtr<ctn::Texture>& sheet);

  ~Skeleton() override;

  void tick(IWandererCore& core, float delta) override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;
};

}  // namespace wanderer
