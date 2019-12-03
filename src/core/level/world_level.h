#pragma once
#include "abstract_level.h"

namespace albinjohansson::wanderer {

class WorldLevel final : public AbstractLevel {
 public:
  WorldLevel(ITileMap_uptr tileMap,
             IPlayer_sptr player,
             SoundEngine_sptr soundEngine,
             ImageGenerator& imageGenerator);

  ~WorldLevel() override;
};

}
