#include "sjpch.h"
#include "Application.h"

#include "Sjoko/Events/ApplicationEvent.h"
#include "Sjoko/Log.h"

namespace Sjoko {

  Application::Application()
  {
  }

  Application::~Application()
  {

  }

  void Application::Run()
  {
    WindowResizeEvent e(1280, 720);
    if (e.IsInCategory(EventCategoryApplication))
    {
      SJ_TRACE(e);
    }
    if (e.IsInCategory(EventCategoryInput))
    {
      SJ_TRACE(e);
    }

    while (true);
  }

}