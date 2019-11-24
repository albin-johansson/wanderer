#include "world_level.h"

namespace albinjohansson::wanderer {

WorldLevel::WorldLevel(IPlayer_sptr player,
                       SoundEngine_sptr soundEngine,
                       ImageGenerator& imageGenerator)
    : AbstractLevel(std::move(player), std::move(soundEngine), imageGenerator) {}

WorldLevel::~WorldLevel() = default;

}