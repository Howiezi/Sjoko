#include "sjpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sjoko {

  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}