#include <Sjoko.h>

class ExampleLayer : public Sjoko::Layer
{
public:
  ExampleLayer()
    : Layer("Example")
  {
  }

  void OnUpdate() override
  {
    SJ_INFO("ExampleLayer::Update");
  }

  void OnEvent(Sjoko::Event& event) override
  {
    SJ_TRACE("{0}", event);
  }

};

class Sandbox : public Sjoko::Application
{
public:
  Sandbox()
  {
    PushLayer(new ExampleLayer());
    PushOverlay(new Sjoko::ImGuiLayer());
  }

  ~Sandbox()
  {

  }

};

Sjoko::Application* Sjoko::CreateApplication()
{
  return new Sandbox();
}