#pragma once
#include <string>
#include <memory>

namespace centurion {

class Renderer;
class Image;

}

namespace albinjohansson::wanderer {

/**
 * The ImageGenerator class is used to load images.
 *
 * @since 0.1.0
 */
class ImageGenerator final {
 private:
  std::shared_ptr<centurion::Renderer> renderer = nullptr;

 public:
  /**
   * @param renderer a shared pointer to the associated renderer instance.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit ImageGenerator(const std::shared_ptr<centurion::Renderer>& renderer);

  ~ImageGenerator();

  /**
   * Loads the image at the specified path.
   *
   * @param path the path of the image that will be loaded, including the file extension.
   * @return 0.1.0
   */
  [[nodiscard]]
  std::unique_ptr<centurion::Image> load(const std::string& path) const;

};

}
