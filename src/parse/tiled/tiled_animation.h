#pragma once
#include <vector>

namespace tiled {

struct Frame {
  int tileId = 0;
  int duration = 0;
};

class TiledAnimation {
 public:
  TiledAnimation();

  explicit TiledAnimation(int nFrames);

  ~TiledAnimation();

  void add_frame(Frame frame);

  [[nodiscard]] const std::vector<Frame>& get_frames();

 private:
  std::vector<Frame> m_frames;
};

}  // namespace tiled
