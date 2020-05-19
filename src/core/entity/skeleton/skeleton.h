#pragma once
#include <memory>

#include "abstract_entity.h"
#include "entity_state_machine.h"
#include "game_constants.h"
#include "tile.h"
#include "wanderer_stdinc.h"

namespace wanderer {

class Skeleton final : public AbstractEntity {
 public:
  static constexpr float homingRange = GameConstants::tile_size * 4.0f;

  explicit Skeleton(const SharedPtr<ctn::Texture>& sheet);

  ~Skeleton() override;

  void tick(IWandererCore& core, float delta) override;

  void draw(ctn::Renderer& renderer, const Viewport& viewport) const override;

 private:
  UniquePtr<IEntityStateMachine> m_stateMachine = nullptr;

  void init();
};

}  // namespace wanderer
