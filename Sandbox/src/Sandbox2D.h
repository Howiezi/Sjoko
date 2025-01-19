#pragma once

#include "Sjoko.h"

class Sandbox2D : public Sjoko::Layer
{
public:
  Sandbox2D();
  virtual ~Sandbox2D() = default;

  virtual void OnAttach() override;
  virtual void OnDetach() override;

  void OnUpdate(Sjoko::Timestep ts) override;
  virtual void OnImGuiRender() override;
  void OnEvent(Sjoko::Event& e) override;
private:
  Sjoko::OrthographicCameraController m_CameraController;

  // Temporary
  Sjoko::Ref<Sjoko::VertexArray> m_SquareVA;
  Sjoko::Ref<Sjoko::Shader> m_FlatColorShader;

  Sjoko::Ref<Sjoko::Texture2D> m_CheckerboardTexture;
  Sjoko::Ref<Sjoko::Texture2D> m_SpriteSheet;

  glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

  uint32_t m_MapWidth, m_MapHeight;

  std::unordered_map<char, Sjoko::Ref<Sjoko::SubTexture2D>>s_TextureMap;
};