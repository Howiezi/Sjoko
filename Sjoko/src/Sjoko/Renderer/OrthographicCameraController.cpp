#include "sjpch.h"
#include "OrthographicCameraController.h"

#include "Sjoko/Core/Input.h"
#include "Sjoko/Core/KeyCodes.h"

namespace Sjoko {
  OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
    : m_AspectRatio(aspectRatio), m_Camera(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel), m_Rotation(rotation)
  {

  }

  void OrthographicCameraController::OnUpdate(Timestep ts)
  {
    SJ_PROFILE_FUNCTION();
    
    if (Input::IsKeyPressed(SJ_KEY_A))
    {
      m_CameraPosition.x -= m_CameraTranslationSpeed * ts;
    }
    else if (Input::IsKeyPressed(SJ_KEY_D))
    {
      m_CameraPosition.x += m_CameraTranslationSpeed * ts;
    }
    if (Input::IsKeyPressed(SJ_KEY_S))
    {
      m_CameraPosition.y -= m_CameraTranslationSpeed * ts;
    }
    else if (Input::IsKeyPressed(SJ_KEY_W))
    {
      m_CameraPosition.y += m_CameraTranslationSpeed * ts;
    }
    if (m_Rotation) {
      if (Input::IsKeyPressed(SJ_KEY_Q))
      {
        m_CameraRotation += m_CameraRotationSpeed * ts;
      }
      else if (Input::IsKeyPressed(SJ_KEY_E))
      {
        m_CameraRotation -= m_CameraRotationSpeed * ts;
      }

      m_Camera.SetRotation(m_CameraRotation);
    }

    m_Camera.SetPosition(m_CameraPosition);
  }

  void OrthographicCameraController::OnEvent(Event& e)
  {
    SJ_PROFILE_FUNCTION();

    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<MouseScrolledEvent>(SJ_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
    dispatcher.Dispatch<WindowResizeEvent>(SJ_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
  }

  void OrthographicCameraController::CalculateView()
  {
    m_Camera.SetProjection(-m_AspectRatio * m_ZoomLevel, m_AspectRatio * m_ZoomLevel, -m_ZoomLevel, m_ZoomLevel);
  }

  bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
  {
    SJ_PROFILE_FUNCTION();
    
    m_ZoomLevel -= e.GetYOffset() * 0.25f;
    m_ZoomLevel = std::max(m_ZoomLevel, 0.25f);
    CalculateView();
    return false;
  }

  bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
  {
    SJ_PROFILE_FUNCTION();

    m_AspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
    CalculateView();
    return false;
  }

}