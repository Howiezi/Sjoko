#pragma once

#include "Sjoko/Core/Core.h"
#include "Sjoko/Core/Timestep.h"
#include "Sjoko/Events/Event.h"

namespace Sjoko {

  class SJOKO_API Layer
  {
  public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer();

    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(Timestep ts) {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& event) {}

    inline const std::string& GetName() const { return m_DebugName; }
  protected:
    std::string m_DebugName;
  };

}