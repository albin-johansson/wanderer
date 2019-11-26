#include "world_level.h"

namespace albinjohansson::wanderer {

WorldLevel::WorldLevel(TileMap_uptr tileMap,
                       IPlayer_sptr player,
                       SoundEngine_sptr soundEngine,
                       ImageGenerator& imageGenerator)
    : AbstractLevel(std::move(tileMap),
                    std::move(player),
                    std::move(soundEngine),
                    imageGenerator) {}

WorldLevel::~WorldLevel() = default;

}