#include "image_generator.h"
#include "renderer.h"
#include "image.h"
#include "objects.h"

namespace albinjohansson::wanderer {

ImageGenerator::ImageGenerator(std::shared_ptr<Renderer> renderer) {
  this->renderer = Objects::RequireNonNull(std::move(renderer));
}

ImageGenerator::~ImageGenerator() = default;

std::unique_ptr<Image> ImageGenerator::Load(const std::string& path) const {
  return std::make_unique<Image>(renderer->GetInternalRenderer(), path);
}

}
