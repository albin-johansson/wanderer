#include "texture.hpp"

#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include <stb_image.h>

#include "wanderer/core/error.hpp"
#include "wanderer/core/vocabulary.hpp"

namespace wanderer {
namespace {

struct ImageDeleter {
  void operator()(uint8* data) const noexcept { stbi_image_free(data); }
};

using ImagePtr = Unique<uint8, ImageDeleter>;

}  // namespace

Texture::Texture(const char* filename)
{
  stbi_set_flip_vertically_on_load(true);

  ImagePtr data {stbi_load(filename, &mWidth, &mHeight, nullptr, 4)};

  if (!data) {
    throw Error {"Failed to load texture data!"};
  }

  glGenTextures(1, &mId);
  glBindTexture(GL_TEXTURE_2D, mId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexImage2D(GL_TEXTURE_2D,
               0,
               GL_RGBA,
               mWidth,
               mHeight,
               0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               data.get());
  glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture()
{
  glDeleteTextures(1, &mId);
}

void Texture::bind() const
{
  glBindTexture(GL_TEXTURE_2D, mId);
}

}  // namespace wanderer
