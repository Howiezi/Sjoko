#include <Sjoko.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include "..//vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Sjoko::Layer
{
public:
  ExampleLayer()
    : Layer("Example"), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f), m_CameraPosition(0.0f)
  {
    m_VertexArray.reset(Sjoko::VertexArray::Create());

    float vertices[3 * 7] = {
      -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
       0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
       0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };

    Sjoko::Ref<Sjoko::VertexBuffer> vertexBuffer;
    vertexBuffer.reset(Sjoko::VertexBuffer::Create(vertices, sizeof(vertices)));

    Sjoko::BufferLayout layout = {
      { Sjoko::ShaderDataType::Float3, "a_Position" },
      { Sjoko::ShaderDataType::Float4, "a_Color" }
    };

    vertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[3] = { 0, 1, 2 };
    Sjoko::Ref<Sjoko::IndexBuffer> indexBuffer;
    indexBuffer.reset(Sjoko::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    m_SquareVA.reset(Sjoko::VertexArray::Create());

    float squareVertices[5 * 4] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
       0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
       0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
      -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    Sjoko::Ref<Sjoko::VertexBuffer> squareVB;
    squareVB.reset(Sjoko::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
      { Sjoko::ShaderDataType::Float3, "a_Position" },
      { Sjoko::ShaderDataType::Float2, "a_TexCoord" },
      });
    m_SquareVA->AddVertexBuffer(squareVB);

    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Sjoko::Ref<Sjoko::IndexBuffer> squareIB;
    squareIB.reset(Sjoko::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string vertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec4 a_Color;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_ModelTransform;

      out vec3 v_Position;
      out vec4 v_Color;
      
      void main()
      {
        v_Position = a_Position;
        v_Color = a_Color;
        gl_Position = u_ViewProjection * u_ModelTransform * vec4(a_Position, 1.0);
      }
    )";

    std::string fragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;

      in vec3 v_Position;
      in vec4 v_Color;
      
      void main()
      {
        color = vec4(v_Position * 0.5 + 0.5, 1.0);
        color = v_Color;
      }
    )";

    m_Shader.reset(Sjoko::Shader::Create(vertexSrc, fragmentSrc));

    std::string flatColorVertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;

      out vec3 v_Position;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_ModelTransform;
      
      void main()
      {
        v_Position = a_Position;
        gl_Position = u_ViewProjection * u_ModelTransform * vec4(a_Position, 1.0);
      }
    )";

    std::string flatColorFragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;

      in vec3 v_Position;

      uniform vec3 u_Color;

      void main()
      {
        color = vec4(u_Color, 1.0);
      }
    )";

    m_FlatColorShader.reset(Sjoko::Shader::Create(flatColorVertexSrc, flatColorFragmentSrc));

    std::string textureVertexSrc = R"(
      #version 330 core

      layout(location = 0) in vec3 a_Position;
      layout(location = 1) in vec2 a_TexCoord;

      uniform mat4 u_ViewProjection;
      uniform mat4 u_ModelTransform;

      out vec2 v_TexCoord;
      
      void main()
      {
        v_TexCoord = a_TexCoord;
        gl_Position = u_ViewProjection * u_ModelTransform * vec4(a_Position, 1.0);
      }
    )";

    std::string textureFragmentSrc = R"(
      #version 330 core

      layout(location = 0) out vec4 color;

      in vec2 v_TexCoord;

      uniform sampler2D u_Texture;

      void main()
      {
        color = texture(u_Texture, v_TexCoord);
      }
    )";

    m_TextureShader.reset(Sjoko::Shader::Create(textureVertexSrc, textureFragmentSrc));

    m_Texture = Sjoko::Texture2D::Create("assets/textures/Checkerboard.png");
    m_AlphaTexture = Sjoko::Texture2D::Create("assets/textures/AlphaTexture.png");

    std::dynamic_pointer_cast<Sjoko::OpenGLShader>(m_TextureShader)->Bind();
    std::dynamic_pointer_cast<Sjoko::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);
  }

  void OnUpdate(Sjoko::Timestep ts) override
  {
    if (Sjoko::Input::IsKeyPressed(SJ_KEY_A))
    {
      m_CameraPosition.x -= m_CameraSpeed * ts;
    }
    else if (Sjoko::Input::IsKeyPressed(SJ_KEY_D))
    {
      m_CameraPosition.x += m_CameraSpeed * ts;
    }
    if (Sjoko::Input::IsKeyPressed(SJ_KEY_S))
    {
      m_CameraPosition.y -= m_CameraSpeed * ts;
    }
    else if (Sjoko::Input::IsKeyPressed(SJ_KEY_W))
    {
      m_CameraPosition.y += m_CameraSpeed * ts;
    }
    if (Sjoko::Input::IsKeyPressed(SJ_KEY_Q))
    {
      m_CameraRotation += m_CameraRotationSpeed * ts;
    }
    else if (Sjoko::Input::IsKeyPressed(SJ_KEY_E))
    {
      m_CameraRotation -= m_CameraRotationSpeed * ts;
    }

    Sjoko::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Sjoko::RenderCommand::Clear();

    m_Camera.SetPosition(m_CameraPosition);
    m_Camera.SetRotation(m_CameraRotation);

    Sjoko::Renderer::BeginScene(m_Camera);

    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

    std::dynamic_pointer_cast<Sjoko::OpenGLShader>(m_FlatColorShader)->Bind();
    std::dynamic_pointer_cast<Sjoko::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

    for (int y = 0; y < 20; y++)
    {
      for (int x = 0; x < 20; x++)
      {
        glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
        Sjoko::Renderer::Submit(m_SquareVA, m_FlatColorShader, transform);
      }
    }

    m_Texture->Bind();
    Sjoko::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
    m_AlphaTexture->Bind();
    Sjoko::Renderer::Submit(m_SquareVA, m_TextureShader, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

    // Triangle
    // Sjoko::Renderer::Submit(m_VertexArray, m_Shader);

    Sjoko::Renderer::EndScene();
  }

  virtual void OnImGuiRender() override
  {
    ImGui::Begin("Settings");
    ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
    ImGui::End();
  }

  void OnEvent(Sjoko::Event& event) override
  {
  }

private:
  Sjoko::Ref<Sjoko::Shader> m_Shader;
  Sjoko::Ref<Sjoko::VertexArray> m_VertexArray;

  Sjoko::Ref<Sjoko::Shader> m_FlatColorShader, m_TextureShader;
  Sjoko::Ref<Sjoko::VertexArray> m_SquareVA;

  Sjoko::Ref<Sjoko::Texture2D> m_Texture, m_AlphaTexture;

  Sjoko::OrthographicCamera m_Camera;
  glm::vec3 m_CameraPosition;
  float m_CameraRotation = 0.0f;
  float m_CameraSpeed = 5.0f;
  float m_CameraRotationSpeed = 90.0f;

  glm::vec3 m_SquareColor;
};

class Sandbox : public Sjoko::Application
{
public:
  Sandbox()
  {
    PushLayer(new ExampleLayer());
  }

  ~Sandbox()
  {

  }

};

Sjoko::Application* Sjoko::CreateApplication()
{
  return new Sandbox();
}