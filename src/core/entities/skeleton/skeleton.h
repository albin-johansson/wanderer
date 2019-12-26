#pragma once
#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "tile.h"
#include <memory>

namespace albinjohansson::wanderer {

class Skeleton final : public AbstractEntity {
 private:
  std::unique_ptr<IEntityStateMachine> stateMachine = nullptr;

 public:
  static constexpr float HOMING_RANGE = Tile::SIZE * 4.0f;

  explicit Skeleton(const std::shared_ptr<Image>& sheet);

  ~Skeleton() override;

  void Tick(IWandererCore& core, float delta) override;

  void Draw(const Renderer& renderer, const Viewport& viewport) const override;

};

}
