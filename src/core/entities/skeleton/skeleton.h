#pragma once
#include <memory>
#include "wanderer_stdinc.h"
#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "tile.h"
#include "game_constants.h"

namespace albinjohansson::wanderer {

class Skeleton final : public AbstractEntity {
 private:
  unique<IEntityStateMachine> stateMachine = nullptr;

  void init();

 public:
  static constexpr float HOMING_RANGE = GameConstants::tile_size * 4.0f;

  explicit Skeleton(const shared<centurion::Image>& sheet);

  ~Skeleton() override;

  void tick(IWandererCore& core, float delta) override;

  void draw(const centurion::Renderer& renderer, const Viewport& viewport) const override;

};

}
