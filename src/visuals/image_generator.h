#pragma once
#include <string>
#include <memory>

namespace albinjohansson::wanderer {

class Renderer;
class Image;

/**
 * The ImageGenerator class is used to load images.
 *
 * @since 0.1.0
 */
class ImageGenerator final {
 private:
  std::shared_ptr<Renderer> renderer = nullptr;

 public:
  /**
   * @param renderer a shared pointer to the associated renderer instance.
   * @throws NullPointerException if the supplied pointer is null.
   * @since 0.1.0
   */
  explicit ImageGenerator(std::shared_ptr<Renderer> renderer);

  ~ImageGenerator();

  /**
   * Loads the image at the specified path.
   *
   * @param path the path of the image that will be loaded, including the file extension.
   * @return 0.1.0
   */
  [[nodiscard]]
  std::unique_ptr<Image> Load(const std::string& path) const;

};

}
