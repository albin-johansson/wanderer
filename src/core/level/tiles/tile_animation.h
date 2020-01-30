#pragma once
#include <unordered_map>
#include <cstdint>
#include "wanderer_stdinc.h"
#include "tile_id.h"

namespace albinjohansson::wanderer {

struct Frame {
  TileID frameId = 0;
  uint32 duration = 100;
};

class TileAnimation final {
 private:
  std::unordered_map<int, Frame> frames;
  int nFrames = 1;
  int index = 0;
  uint32 previous = 0;

 public:
  TileAnimation();

  explicit TileAnimation(int nFrames);

  ~TileAnimation();

  void update();

  void set_frame(int index, Frame frame);

  [[nodiscard]]
  Frame get_frame() const;

};

}
