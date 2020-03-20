#pragma once

#include <string>
#include <unordered_map>
#include <vector>

#include <SFML/Window/Window.hpp>
#include <glm/fwd.hpp>

#include "afk/render/ShaderData.hpp"
#include "afk/render/opengl/MeshHandle.hpp"
#include "afk/render/opengl/ModelHandle.hpp"
#include "afk/render/opengl/ShaderHandle.hpp"
#include "afk/render/opengl/ShaderProgramHandle.hpp"
#include "afk/render/opengl/TextureHandle.hpp"

namespace Afk {
  struct Model;
  struct MeshData;
  struct ModelData;
  struct TextureData;

  namespace OpenGl {
    class Renderer {
    public:
      using MeshHandle          = OpenGl::MeshHandle;
      using ModelHandle         = OpenGl::ModelHandle;
      using ShaderHandle        = OpenGl::ShaderHandle;
      using ShaderProgramHandle = OpenGl::ShaderProgramHandle;
      using TextureHandle       = OpenGl::TextureHandle;

      using ShaderHandlesMap = std::unordered_map<std::string, ShaderHandle>;
      using ShaderProgramHandlesMap = std::unordered_map<std::string, ShaderProgramHandle>;
      using ModelHandlesMap   = std::unordered_map<std::string, ModelHandle>;
      using TextureHandlesMap = std::unordered_map<std::string, TextureHandle>;

      using ShaderHandles = std::vector<ShaderHandle>;

      sf::Window window = {};

      Renderer();

      auto clearScreen(glm::vec4 clearColor = {1.0f, 1.0f, 1.0f, 1.0f}) const -> void;
      auto swapBuffers() -> void;
      auto setViewport(int x, int y, unsigned width, unsigned height) const -> void;
      auto drawModel(const ModelHandle &model, const ShaderProgramHandle &shader) const
          -> void;
      auto useShader(const ShaderProgramHandle &shader) const -> void;
      auto setTextureUnit(std::size_t unit) const -> void;
      auto bindTexture(const TextureHandle &texture) const -> void;

      auto getModel(const std::string &path) -> ModelHandle &;
      auto getTexture(const std::string &path) -> TextureHandle &;
      auto getShader(const std::string &path) -> ShaderHandle &;
      auto getShaderProgram(const std::string &name) -> ShaderProgramHandle &;

      auto loadModel(const ModelData &modelData) -> ModelHandle;
      auto loadTexture(const TextureData &textureData) -> TextureHandle;
      auto compileShader(const ShaderData &shaderData) -> ShaderHandle;
      auto linkShaders(const std::string &name, const ShaderHandles &shaderHandles)
          -> ShaderProgramHandle;
      auto loadMesh(const MeshData &meshData) -> MeshHandle;

      auto setUniform(const ShaderProgramHandle &shader,
                      const std::string &name, bool value) const -> void;
      auto setUniform(const ShaderProgramHandle &shader,
                      const std::string &name, int value) const -> void;
      auto setUniform(const ShaderProgramHandle &shader,
                      const std::string &name, float value) const -> void;
      auto setUniform(const ShaderProgramHandle &shader,
                      const std::string &name, glm::vec3 value) const -> void;
      auto setUniform(const ShaderProgramHandle &shader,
                      const std::string &name, glm::mat4 value) const -> void;

    private:
      ModelHandlesMap models                 = {};
      TextureHandlesMap textures             = {};
      ShaderHandlesMap shaders               = {};
      ShaderProgramHandlesMap shaderPrograms = {};
    };
  }
}