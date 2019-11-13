#pragma once
#include "image.h"
#include "renderer.h"
#include <string>
#include <memory>

namespace wanderer::visuals {

/**
 * The ImageGenerator class is used to load images.
 *
 * @since 0.1.0
 */
class ImageGenerator final {
 private:
  Renderer_sptr renderer = nullptr;

 public:
  /**
   * @param renderer a shared pointer to the associated renderer instance.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit ImageGenerator(Renderer_sptr renderer);

  ~ImageGenerator();

  /**
   * Loads the image at the specified path.
   *
   * @param path the path of the image that will be loaded, including the file extension.
   * @return 0.1.0
   */
  Image_uptr Load(const std::string& path) const;

};

using ImageGenerator_uptr = std::unique_ptr<ImageGenerator>;
using ImageGenerator_sptr = std::shared_ptr<ImageGenerator>;
using ImageGenerator_wptr = std::weak_ptr<ImageGenerator>;

}
