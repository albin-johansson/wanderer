#pragma once
#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "image.h"

namespace wanderer::core {

class Skeleton final : public AbstractEntity {
 private:
  IEntityStateMachine_uptr stateMachine = nullptr;

 public:
  explicit Skeleton(visuals::Image_sptr sheet);

  ~Skeleton() override;

  void Tick(const IGame& game, float delta) override;

  void Draw(visuals::Renderer& renderer, const Viewport& viewport) const override;

};

}
