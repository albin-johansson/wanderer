#pragma once
#include <vector>

namespace albinjohansson::tiled {

struct Frame {
  int tileId = 0;
  int duration = 0;
};

class TiledAnimation {
 private:
  std::vector<Frame> frames;

 public:
  TiledAnimation();

  explicit TiledAnimation(int nFrames);

  ~TiledAnimation();

  void add_frame(Frame frame);

  [[nodiscard]]
  const std::vector<Frame>& get_frames();
};

}
