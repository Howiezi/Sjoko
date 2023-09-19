#include "sjpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Sjoko {


  VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
    switch (Renderer::GetAPI()) 
    {
      case RendererAPI::API::None:     SJ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::OpenGL:   return new OpenGLVertexBuffer(vertices, size);
    }

    SJ_CORE_ASSERT(false, "Unknows RendererAPI");
    return nullptr;
  }

  IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t size) {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::None:     SJ_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::OpenGL:   return new OpenGLIndexBuffer(indices, size);
    }

    SJ_CORE_ASSERT(false, "Unknows RendererAPI");
    return nullptr;
  }


}