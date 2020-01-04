#pragma once
#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "tile.h"
#include "game_constants.h"
#include <memory>

namespace albinjohansson::wanderer {

class Skeleton final : public AbstractEntity {
 private:
  std::unique_ptr<IEntityStateMachine> stateMachine = nullptr;

  void Init();

 public:
  static constexpr float HOMING_RANGE = tileSize * 4.0f;

  explicit Skeleton(const std::shared_ptr<Image>& sheet);

  ~Skeleton() override;

  void tick(IWandererCore& core, float delta) override;

  void Draw(const Renderer& renderer, const Viewport& viewport) const override;

};

}
