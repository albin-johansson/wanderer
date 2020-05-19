#pragma once
#include <unordered_map>

#include "tile_id.h"
#include "wanderer_stdinc.h"

namespace wanderer {

struct Frame {
  TileID frameId = 0;
  uint32 duration = 100;
};

class TileAnimation final {
 public:
  TileAnimation();

  explicit TileAnimation(int nFrames);

  ~TileAnimation();

  void update();

  void set_frame(int index, Frame frame);

  [[nodiscard]] Frame get_frame() const;

 private:
  std::unordered_map<int, Frame> m_frames;
  int m_nFrames = 1;
  int m_index = 0;
  uint32 m_previous = 0;
};

}  // namespace wanderer
