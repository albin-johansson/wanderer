#include "tiled_animation.h"

namespace albinjohansson::tiled {

TiledAnimation::TiledAnimation(int nFrames) {
  frames.reserve(nFrames);
  for (int i = 0; i < nFrames; i++) {
    frames.push_back((Frame) {0, 0});
  }
}

TiledAnimation::~TiledAnimation() = default;

void TiledAnimation::AddFrame(int index, Frame frame) {
  frames.at(index) = frame;
}

const std::vector<Frame>& TiledAnimation::GetFrames() {
  return frames;
}

}
