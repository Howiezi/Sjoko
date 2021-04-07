#include <Sjoko.h>

class Sandbox : public Sjoko::Application
{
public:
  Sandbox()
  {

  }

  ~Sandbox()
  {

  }

};

Sjoko::Application* Sjoko::CreateApplication()
{
  return new Sandbox();
}