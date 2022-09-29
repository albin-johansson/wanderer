#include "shader_program.hpp"

#include <GL/glew.h>
#include <spdlog/spdlog.h>

#include "wanderer/core/error.hpp"
#include "wanderer/gfx/shader.hpp"

namespace wanderer {

ShaderProgram::ShaderProgram(const char* vertex_path, const char* fragment_path)
    : mId {glCreateProgram()}
{
  const Shader vertex_shader {ShaderType::Vertex, vertex_path};
  const Shader fragment_shader {ShaderType::Fragment, fragment_path};

  glAttachShader(mId, vertex_shader.id());
  glAttachShader(mId, fragment_shader.id());

  glLinkProgram(mId);

  int success {};
  glGetProgramiv(mId, GL_LINK_STATUS, &success);

  if (!success) {
    char buf[512];
    glGetProgramInfoLog(mId, sizeof buf, nullptr, buf);

    spdlog::error("Shader program linker error: {}", buf);
    throw Error {"Failed to link shader program!"};
  }
}

ShaderProgram::~ShaderProgram()
{
  glDeleteProgram(mId);
}

void ShaderProgram::use() const
{
  glUseProgram(mId);
}

void ShaderProgram::set_uniform(const char* name, const bool value)
{
  glUniform1i(glGetUniformLocation(mId, name), value ? GL_TRUE : GL_FALSE);
}

void ShaderProgram::set_uniform(const char* name, const int value)
{
  glUniform1i(glGetUniformLocation(mId, name), value);
}

void ShaderProgram::set_uniform(const char* name, const float value)
{
  glUniform1f(glGetUniformLocation(mId, name), value);
}

}  // namespace wanderer