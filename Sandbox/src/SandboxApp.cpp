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
    //SJ_INFO("ExampleLayer::Update");

    if (Sjoko::Input::IsKeyPressed(SJ_KEY_TAB))
      SJ_INFO("Tab key is pressed!");
  }

  void OnEvent(Sjoko::Event& event) override
  {
    //SJ_TRACE("{0}", event);
    if (event.GetEventType() == Sjoko::EventType::KeyPressed) {
      Sjoko::KeyPressedEvent& e = (Sjoko::KeyPressedEvent&)event;
      SJ_TRACE("{0}", (char)e.GetKeyCode());
    }
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