#pragma once

#include "Sjoko.h"

namespace Sjoko {

  class PulverLayer : public Layer
  {
  public:
    PulverLayer();
    virtual ~PulverLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(Timestep ts) override;
    virtual void OnImGuiRender() override;
    void OnEvent(Event& e) override;
  private:
    OrthographicCameraController m_CameraController;

    // Temporary
    Ref<VertexArray> m_SquareVA;
    Ref<Shader> m_FlatColorShader;

    Ref<Texture2D> m_CheckerboardTexture;
    Ref<Texture2D> m_SpriteSheet;

    glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

    uint32_t m_MapWidth, m_MapHeight;

    std::unordered_map<char, Ref<SubTexture2D>>s_TextureMap;
  };

}