#pragma once
#include "wanderer_stdinc.h"

namespace wanderer {

enum class SoundID { SwordSwing };

WANDERER_SERIALIZE_ENUM(SoundID, {{SoundID::SwordSwing, "SwordSwing"}})

}  // namespace wanderer
