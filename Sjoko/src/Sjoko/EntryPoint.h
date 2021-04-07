#pragma once

#ifdef  SJ_PLATFORM_WINDOWS

extern Sjoko::Application* Sjoko::CreateApplication();

int main(int argc, char** argv)
{
  auto app = Sjoko::CreateApplication();
  app->Run();
  delete app;
}

#endif //  SJ_PLATFORM_WINDOWS