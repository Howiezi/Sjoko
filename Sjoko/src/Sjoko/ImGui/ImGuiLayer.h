#pragma once

#include "Sjoko/Core/Layer.h"

#include "Sjoko/Events/ApplicationEvent.h"
#include "Sjoko/Events/KeyEvent.h"
#include "Sjoko/Events/MouseEvent.h"

namespace Sjoko {
  class SJOKO_API ImGuiLayer : public Layer
  {
  public:
    ImGuiLayer();
    ~ImGuiLayer();

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void Begin();
    void End();
  private:
    float m_Time = 0.0f;
  };

}