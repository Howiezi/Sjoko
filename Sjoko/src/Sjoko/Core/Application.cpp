#include "sjpch.h"
#include "Application.h"

#include "Sjoko/Renderer/Renderer.h"

#include "Input.h"

#include <GLFW/glfw3.h>

namespace Sjoko {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

  Application* Application::s_Instance = nullptr;

  Application::Application()
  {
    SJ_PROFILE_FUNCTION();

    SJ_CORE_ASSERT(!s_Instance, "Application already exists!")
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    Renderer::Init();

    m_ImGuiLayer = new ImGuiLayer();
    PushOverlay(m_ImGuiLayer);
  }

  Application::~Application()
  {
    SJ_PROFILE_FUNCTION();

    Renderer::Shutdown();
  }

  void Application::PushLayer(Layer* layer) 
  {
    SJ_PROFILE_FUNCTION();
    
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
  }

  void Application::PushOverlay(Layer* layer)
  {
    SJ_PROFILE_FUNCTION();
    
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
  }

  void Application::OnEvent(Event& e)
  {
    SJ_PROFILE_FUNCTION();
    
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
    dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

    //SJ_CORE_TRACE(e);

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
    {
      (*--it)->OnEvent(e);
      if (e.Handled)
      {
        break;
      }
    }
  }

  void Application::Run()
  {
    SJ_PROFILE_FUNCTION();
    
    while (m_Running)
    {
      SJ_PROFILE_SCOPE("RunLoop");
      
      float time = (float)glfwGetTime(); // Platform::GetTime
      Timestep timestep = time - m_LastFrameTime;
      m_LastFrameTime = time;

      if (!m_Minimized)
      {
        {
          SJ_PROFILE_SCOPE("LayerStack OnUpdate");

          for (Layer* layer : m_LayerStack)
          {
            layer->OnUpdate(timestep);
          }
        }

        m_ImGuiLayer->Begin();
        {
          SJ_PROFILE_SCOPE("LayerStack OnImGuiRender");
          
          for (Layer* layer : m_LayerStack)
          {
            layer->OnImGuiRender();
          }
        }
        m_ImGuiLayer->End();
      }


      m_Window->OnUpdate();
    }
  }

  bool Application::OnWindowClose(WindowCloseEvent& e)
  {
    m_Running = false;
    return true;
  }

  bool Application::OnWindowResize(WindowResizeEvent& e)
  {
    SJ_PROFILE_FUNCTION();
    
    if (e.GetWidth() == 0 || e.GetHeight() == 0)
    {
      m_Minimized = true;
      return false;
    }

    m_Minimized = false;
    Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

    return false;
  }

}