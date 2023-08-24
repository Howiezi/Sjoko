#include "sjpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"

#include "Sjoko/Application.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sjoko {

  ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
  {
  }

  ImGuiLayer::~ImGuiLayer()
  {

  }

  void ImGuiLayer::OnAttach()
  {
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO& io = ImGui::GetIO();
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

    // 
  }

  void ImGuiLayer::OnDetach()
  {
  
  }

  void ImGuiLayer::OnUpdate()
  {
    //ImGuiIO& io = ImGui::GetIO();
    //Application& app = Application::Get();
    //io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

    //float time = (float)glfwGetTime();
    //io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
    //m_Time = time;

    //ImGui::NewFrame();

    //static bool show = true;
    //ImGui::ShowDemoWindow(&show);

    //ImGui::Render();
  }

  void ImGuiLayer::OnEvent(Event& event)
  {
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<MouseButtonPressedEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
    dispatcher.Dispatch<MouseButtonReleasedEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
    dispatcher.Dispatch<MouseMovedEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
    dispatcher.Dispatch<MouseScrolledEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
    dispatcher.Dispatch<KeyPressedEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
    dispatcher.Dispatch<KeyTypedEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
    dispatcher.Dispatch<KeyReleasedEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
    dispatcher.Dispatch<WindowResizeEvent>(SJ_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
  }

  bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = true;

    return false;
  }

  bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseDown[e.GetMouseButton()] = false;

    return false;
  }

  bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MousePos = ImVec2(e.GetX(), e.GetY());

    return false;
  }

  bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.MouseWheelH += e.GetXOffset();
    io.MouseWheel += e.GetYOffset();

    return false;
  }

  bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.GetKeyCode()] = true;

    io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
    io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
    io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
    io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
    return false;
  }

  bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.KeysDown[e.GetKeyCode()] = false;

    return false;
  }

  bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    int keycode = e.GetKeyCode();
    if (keycode > 0 && keycode < 0.10000) {
      io.AddInputCharacter((unsigned short)keycode);
    }

    return false;
  }

  bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
  {
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
    io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
    glViewport(0, 0, e.GetWidth(), e.GetHeight());

    return false;
  }

}