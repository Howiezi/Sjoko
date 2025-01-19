#include "Sandbox2D.h"
#include "..//vendor/imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static const uint32_t s_mapWidth = 24;
static const char* s_MapTiles = 
"000000000000000000000000"
"000000000000000000000000"
"000000000000000000000000"
"000000000000000000000000"
"000000000000000000000000"
"0000CGGGGGGGGGGGGGGV0000"
"0000LDDDDDDDDDDDDDDR0000"
"0000LDDDDDDDDDDDDDDR0000"
"0000LDDDDDDDDDDDDDDR0000"
"0000LDDDDDDDDDDDDDDR0000"
"0000LDDDDDDDDDDDDDDR0000"
"0000LDDDDDDDDDDDDDDR0000"
;

Sandbox2D::Sandbox2D()
  : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
  SJ_PROFILE_FUNCTION();
  
  m_CheckerboardTexture = Sjoko::Texture2D::Create("assets/textures/Checkerboard.png");
  m_SpriteSheet = Sjoko::Texture2D::Create("assets/textures/Atlas/Tilemap/tilemap_packed.png");

  m_MapWidth = s_mapWidth;
  m_MapHeight = strlen(s_MapTiles) / s_mapWidth;

  s_TextureMap['0'] = Sjoko::SubTexture2D::CreateFromCoords(m_SpriteSheet, {0,9}, {8,8});
  s_TextureMap['G'] = Sjoko::SubTexture2D::CreateFromCoords(m_SpriteSheet, {4,7}, { 8,8 });
  s_TextureMap['C'] = Sjoko::SubTexture2D::CreateFromCoords(m_SpriteSheet, {3,5}, {8,8});
  s_TextureMap['V'] = Sjoko::SubTexture2D::CreateFromCoords(m_SpriteSheet, {4,5}, {8,8});
  s_TextureMap['L'] = Sjoko::SubTexture2D::CreateFromCoords(m_SpriteSheet, {5,8}, {8,8});
  s_TextureMap['R'] = Sjoko::SubTexture2D::CreateFromCoords(m_SpriteSheet, {3,8}, {8,8});
  s_TextureMap['D'] = Sjoko::SubTexture2D::CreateFromCoords(m_SpriteSheet, {2,8}, {8,8});
}

void Sandbox2D::OnDetach()
{
  SJ_PROFILE_FUNCTION();

}

void Sandbox2D::OnUpdate(Sjoko::Timestep ts)
{
  SJ_PROFILE_FUNCTION();

  // Update
  m_CameraController.OnUpdate(ts);

  // Render
  Sjoko::Renderer2D::ResetStats();
  {
    SJ_PROFILE_SCOPE("RendererPrep::OnUpdate");
    Sjoko::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Sjoko::RenderCommand::Clear();
  }

#if 0
  {
    static float rotation = 0.0f;
    rotation += ts * 50.0f;

    SJ_PROFILE_SCOPE("RendererDraw::OnUpdate");
    Sjoko::Renderer2D::BeginScene(m_CameraController.GetCamera());

    Sjoko::Renderer2D::DrawRotatedQuad({ 0.0f, -2.0f }, { 0.8f, 0.8f }, glm::radians(45.0f), { 0.2f, 0.8f, 0.8f, 1.0f });
    Sjoko::Renderer2D::DrawRotatedQuad({ 2.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(rotation), m_CheckerboardTexture, 1.0f, { 0.8f, 0.8f, 0.3f, 1.0f });
    Sjoko::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
    Sjoko::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
    Sjoko::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 5.0f);
    Sjoko::Renderer2D::EndScene();

    Sjoko::Renderer2D::BeginScene(m_CameraController.GetCamera());
    for (float y = -5.0f; y < 5.0f; y += 0.5f)
    {
      for (float x = -5.0f; x < 5.0f; x += 0.5f)
      {
        glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
        Sjoko::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
      }
    }
    Sjoko::Renderer2D::EndScene();
  }
#endif

  Sjoko::Renderer2D::BeginScene(m_CameraController.GetCamera());

  for (uint32_t y = 0; y < m_MapHeight; y++)
  {
    for (uint32_t x = 0; x < m_MapWidth; x++)
    {
      char tileType = s_MapTiles[x + y * m_MapWidth];
      Sjoko::Ref<Sjoko::SubTexture2D> texture;

      if (s_TextureMap.find(tileType) != s_TextureMap.end())
      {
        texture = s_TextureMap[tileType];
      }

      Sjoko::Renderer2D::DrawQuad({ x - m_MapWidth / 2.0f , m_MapHeight- y - m_MapHeight / 2.0f, 0.5f }, { 1.0f, 1.0f }, texture);
    }
  }

  Sjoko::Renderer2D::EndScene();

}

void Sandbox2D::OnImGuiRender()
{
  SJ_PROFILE_FUNCTION();

  ImGui::Begin("Settings");

  auto stats = Sjoko::Renderer2D::GetStats();
  ImGui::Text("Renderer2D Stats:");
  ImGui::Text("Draw Calls: %d", stats.DrawCalls);
  ImGui::Text("Quads: %d", stats.QuadCount);
  ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
  ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

  ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
  ImGui::End();
}

void Sandbox2D::OnEvent(Sjoko::Event& e)
{
  m_CameraController.OnEvent(e);
}