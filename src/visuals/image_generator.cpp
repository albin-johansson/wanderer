#include "image_generator.h"
#include "objects.h"

using namespace wanderer::core;

namespace wanderer::visuals {

ImageGenerator::ImageGenerator(Renderer_sptr renderer) {
  this->renderer = Objects::RequireNonNull(std::move(renderer));
}

ImageGenerator::~ImageGenerator() = default;

ImageGenerator_uptr ImageGenerator::Create(Renderer_sptr renderer) {
  return std::make_unique<ImageGenerator>(renderer);
}

Image_uptr ImageGenerator::Load(const std::string& path) const {
  return std::make_unique<Image>(renderer->GetInternalRenderer(), path);
}

}
