#include "shader.hpp"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "wanderer/core/error.hpp"
#include "wanderer/io/files.hpp"

namespace wanderer {

Shader::Shader(const ShaderType type, const char* filename)
    : mId {glCreateShader(type == ShaderType::Vertex ? GL_VERTEX_SHADER
                                                     : GL_FRAGMENT_SHADER)}
{
  const auto source = load_file_into_string(filename);
  const auto* source_ptr = source.c_str();

  glShaderSource(mId, 1, &source_ptr, nullptr);
  glCompileShader(mId);

  int success {};
  glGetShaderiv(mId, GL_COMPILE_STATUS, &success);

  if (!success) {
    char buf[512];
    glGetShaderInfoLog(mId, sizeof buf, nullptr, buf);
    spdlog::error("Shader compilation error: {}", buf);

    throw Error {"Failed to compile shader!"};
  }
}

Shader::~Shader()
{
  spdlog::debug("Deleting shader {}...", mId);
  glDeleteShader(mId);
}

}  // namespace wanderer