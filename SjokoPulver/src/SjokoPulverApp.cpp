#include <Sjoko.h>
#include <Sjoko/Core/EntryPoint.h>

#include "PulverLayer.h"

namespace Sjoko {
  
  class SjokoPulver : public Application
  {
  public:
    SjokoPulver()
      : Application("SjokoPulver")
    {
      PushLayer(new PulverLayer());
    }

    ~SjokoPulver()
    {
    }
  };

  Application* CreateApplication()
  {
    return new SjokoPulver();
  }
}