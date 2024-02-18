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
    SJ_PROFILE_FUNCTION();

    glfwMakeContextCurrent(m_WindowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    SJ_CORE_ASSERT(status, "Failed to initialize Glad!");

    SJ_CORE_INFO("OpenGL Info:");
    SJ_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
    SJ_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
    SJ_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

  #ifdef SJ_ENABLE_ASSERTS
     int versionMajor;
     int versionMinor;
     glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
     glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

     SJ_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Sjoko requires at least OpenGL version 4.5!");
  #endif
  }

  void OpenGLContext::SwapBuffers() {
    SJ_PROFILE_FUNCTION();

    glfwSwapBuffers(m_WindowHandle);
  }
}