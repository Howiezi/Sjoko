#pragma once

#include "RenderCommand.h"

#include "Sjoko/Renderer/OrthographicCamera.h"
#include "Shader.h"

namespace Sjoko {

  class Renderer {
  public:
    static void BeginScene(OrthographicCamera& camera);
    static void EndScene();

    static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

    inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
  private:
    struct SceneData
    {
      glm::mat4 ViewProjectionMatrix;
    };

    static SceneData* m_SceneData;
  };

}