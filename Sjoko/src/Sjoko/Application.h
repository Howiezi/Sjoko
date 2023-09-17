#pragma once

#include "Core.h"

#include "Window.h"
#include "Sjoko/LayerStack.h"
#include "Sjoko/Events/Event.h"
#include "Sjoko/Events/ApplicationEvent.h"

#include "Sjoko/ImGui/ImGuiLayer.h"

#include "Sjoko/Renderer/Shader.h"
#include "Sjoko/Renderer/Buffer.h"

namespace Sjoko {

  class SJOKO_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* layer);
    void PushOverlay(Layer* layer);
    
    inline Window& GetWindow() { return *m_Window; }

    inline static Application& Get() { return *s_Instance; }
  private:
    bool OnWindowClose(WindowCloseEvent& e);

    std::unique_ptr<Window> m_Window;
    ImGuiLayer* m_ImGuiLayer;
    bool m_Running = true;
    LayerStack m_LayerStack;

    unsigned int m_VertexArray;
    std::unique_ptr<Shader> m_Shader;
    std::unique_ptr<VertexBuffer> m_VertexBuffer;
    std::unique_ptr<IndexBuffer> m_IndexBuffer;

    static Application* s_Instance;
  };

  // To be defined in CLIENT
  Application* CreateApplication();

}