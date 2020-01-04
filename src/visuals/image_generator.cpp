#include "image_generator.h"
#include "renderer.h"
#include "image.h"
#include "require.h"

using namespace centurion;

namespace albinjohansson::wanderer {

ImageGenerator::ImageGenerator(const std::shared_ptr<Renderer>& renderer) {
  this->renderer = Require::not_null(renderer);
}

ImageGenerator::~ImageGenerator() = default;

std::unique_ptr<Image> ImageGenerator::load(const std::string& path) const {
  return std::make_unique<Image>(*renderer, path);
}

}
