#pragma once
#include "tile_id.h"

namespace albinjohansson::wanderer {

struct TileObject final { // FIXME might be removed
  float x = 0;
  float y = 0;
  TileID id = 0;
  int group = 0;
  int renderGroup = 0;
  bool pivot = false;
};

}
