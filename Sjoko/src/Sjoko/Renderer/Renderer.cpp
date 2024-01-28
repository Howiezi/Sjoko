#include "sjpch.h"
#include "Renderer.h"

namespace Sjoko {

  Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;
  
  void Renderer::BeginScene(OrthographicCamera& camera) {
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
  }

  void Renderer::EndScene() {

  }

  void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader, const glm::mat4& transform) {
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    shader->UploadUniformMat4("u_ModelTransform", transform);

    vertexArray->Bind();
    RenderCommand::DrawIndexed(vertexArray);
  }

}