#pragma once
#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "image.h"
#include "tile.h"

namespace albinjohansson::wanderer {

class Skeleton final : public AbstractEntity {
 private:
  IEntityStateMachine_uptr stateMachine = nullptr;

 public:
  static constexpr float HOMING_RANGE = Tile::SIZE * 4.0f;
  
  explicit Skeleton(Image_sptr sheet);

  ~Skeleton() override;

  void Tick(IWandererCore& core, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

};

}
