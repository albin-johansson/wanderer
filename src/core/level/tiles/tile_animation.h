#pragma once
#include "tile_id.h"
#include <unordered_map>
#include <cstdint>

namespace albinjohansson::wanderer {

struct Frame {
  TileID frameId = 0;
  uint32_t duration = 100;
};

class TileAnimation final {
 private:
  std::unordered_map<int, Frame> frames;
  int nFrames = 1;
  int index = 0;
  uint32_t previous = 0;

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
