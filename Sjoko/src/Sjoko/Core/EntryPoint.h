#pragma once

#ifdef  SJ_PLATFORM_WINDOWS

extern Sjoko::Application* Sjoko::CreateApplication();

int main(int argc, char** argv)
{
  Sjoko::Log::Init();

  SJ_PROFILE_BEGIN_SESSION("Startup", "SjokoProfile-Startup.json");
  auto app = Sjoko::CreateApplication();
  SJ_PROFILE_END_SESSION();

  SJ_PROFILE_BEGIN_SESSION("Runtime", "SjokoProfile-Runtime.json");
  app->Run();
  SJ_PROFILE_END_SESSION();

  SJ_PROFILE_BEGIN_SESSION("Shutdown", "SjokoProfile-Shutdown.json");
  delete app;
  SJ_PROFILE_END_SESSION();

}

#endif //  SJ_PLATFORM_WINDOWS