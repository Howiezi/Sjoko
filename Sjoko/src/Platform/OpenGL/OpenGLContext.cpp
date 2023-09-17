#include "sjpch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sjoko {
  OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
    : m_WindowHandle(windowHandle) {
    SJ_CORE_ASSERT(windowHandle, "Window handle is null!");
  }

  void OpenGLContext::Init() {
    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    SJ_CORE_ASSERT(status, "Failed to initialize Glad!");

    SJ_CORE_INFO("OpenGL Info:");
    SJ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    SJ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    SJ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
  }

  void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(m_WindowHandle);
  }
}