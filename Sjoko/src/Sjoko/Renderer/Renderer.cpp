#include "sjpch.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Sjoko {

  Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

  void Renderer::Init()
  {
    RenderCommand::Init();
  }
  
  void Renderer::BeginScene(OrthographicCamera& camera) {
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene() {

  }

  void Renderer::Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform) {
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ModelTransform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }

}