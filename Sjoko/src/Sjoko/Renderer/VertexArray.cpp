#include "sjpch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Sjoko {

  VertexArray* VertexArray::Create() {
    switch (Renderer::GetAPI()) {
    case RendererAPI::API::None:       SJ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
    case RendererAPI::API::OpenGL:     return new OpenGLVertexArray();
    }

    SJ_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

}