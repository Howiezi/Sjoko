#include "Sandbox2D.h"
#include "..//vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D()
  : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
  m_SquareVA = Sjoko::VertexArray::Create();

  float squareVertices[5 * 4] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.5f,  0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
  };

  Sjoko::Ref<Sjoko::VertexBuffer> squareVB;
  squareVB.reset(Sjoko::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
  squareVB->SetLayout({
    { Sjoko::ShaderDataType::Float3, "a_Position" }
    });
  m_SquareVA->AddVertexBuffer(squareVB);

  uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
  Sjoko::Ref<Sjoko::IndexBuffer> squareIB;
  squareIB.reset(Sjoko::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
  m_SquareVA->SetIndexBuffer(squareIB);

  m_FlatColorShader = Sjoko::Shader::Create("assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Sjoko::Timestep ts)
{
  // Update
  m_CameraController.OnUpdate(ts);

  // Render
  Sjoko::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
  Sjoko::RenderCommand::Clear();

  Sjoko::Renderer::BeginScene(m_CameraController.GetCamera());

  std::dynamic_pointer_cast<Sjoko::OpenGLShader>(m_FlatColorShader)->Bind();
  std::dynamic_pointer_cast<Sjoko::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

  Sjoko::Renderer::Submit(m_SquareVA, m_FlatColorShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

  Sjoko::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
  ImGui::Begin("Settings");
  ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void Sandbox2D::OnEvent(Sjoko::Event& e)
{
  m_CameraController.OnEvent(e);
}