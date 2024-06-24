#ifndef ENGINE_ENTRYPOINT_H
#define ENGINE_ENTRYPOINT_H

//#ifdef DM_PLATFORM_WINDOWS

extern Deimos::Application* Deimos::createApplication();

int main(int argc, char **argv) {
    Deimos::Log::init();

    DM_PROFILE_BEGIN_SESSION("Startup",  std::string(DEBUG_DIR) + "/DebugInfo/DeimosProfile-Startup.json");
    auto app = Deimos::createApplication();
    DM_PROFILE_END_SESSION();

    DM_PROFILE_BEGIN_SESSION("Runtime",  std::string(DEBUG_DIR) + "/DebugInfo/DeimosProfile-Runtime.json");
    app->run();
    DM_PROFILE_END_SESSION();

    DM_PROFILE_BEGIN_SESSION("Shutdown",  std::string(DEBUG_DIR) + "/DebugInfo/DeimosProfile-Shutdown.json");
    delete app;
    DM_PROFILE_END_SESSION();
}

//#endif

#endif //ENGINE_ENTRYPOINT_H
