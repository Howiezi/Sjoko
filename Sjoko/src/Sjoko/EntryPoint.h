#pragma once

#ifdef  SJ_PLATFORM_WINDOWS

extern Sjoko::Application* Sjoko::CreateApplication();

int main(int argc, char** argv)
{
  Sjoko::Log::Init();
  SJ_CORE_WARN("Initialized Log!");
  int a = 5;
  SJ_INFO("Hello! Var={0}", a);


  auto app = Sjoko::CreateApplication();
  app->Run();
  delete app;
}

#endif //  SJ_PLATFORM_WINDOWS