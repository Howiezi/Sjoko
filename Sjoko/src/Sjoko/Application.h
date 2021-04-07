#pragma once

#include "Core.h"

namespace Sjoko {

  class SJOKO_API Application
  {
  public:
    Application();
    virtual ~Application();

    void Run();
  };

  // To be defined in CLIENT
  Application* CreateApplication();

}