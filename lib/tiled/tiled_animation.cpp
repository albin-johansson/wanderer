#include "tiled_animation.h"

namespace tiled {

TiledAnimation::TiledAnimation() = default;

TiledAnimation::TiledAnimation(int nFrames) {
  frames.reserve(nFrames);
}

TiledAnimation::~TiledAnimation() = default;

void TiledAnimation::add_frame(Frame frame) {
  frames.push_back(frame);
}

const std::vector<Frame>& TiledAnimation::get_frames() {
  return frames;
}

}
