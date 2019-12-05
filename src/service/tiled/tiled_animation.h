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

  void AddFrame(Frame frame);

  const std::vector<Frame>& GetFrames();
};

}
