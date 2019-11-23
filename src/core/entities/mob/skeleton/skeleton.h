#pragma once
#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "image.h"

namespace albinjohansson::wanderer {

class Skeleton final : public AbstractEntity {
 private:
  IEntityStateMachine_uptr stateMachine = nullptr;

 public:
  explicit Skeleton(Image_sptr sheet);

  ~Skeleton() override;

  void Tick(const IGame& game, float delta) override;

  void Draw(Renderer& renderer, const Viewport& viewport) const override;

};

}
