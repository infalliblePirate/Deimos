#ifndef ENGINE_ENTRYPOINT_H
#define ENGINE_ENTRYPOINT_H

//#ifdef DM_PLATFORM_WINDOWS

extern Deimos::Application* Deimos::createApplication();

int main(int argc, char **argv) {
    Deimos::Log::init();

    DM_PROFILE_BEGIN_SESSION("Startup", "DeimosProfile-Startup.json");
    auto app = Deimos::createApplication();
    DM_PROFILE_END_SESSION();

    DM_PROFILE_BEGIN_SESSION("Runtime", "DeimosProfile-Runtime.json");
    app->run();
    DM_PROFILE_END_SESSION();

    DM_PROFILE_BEGIN_SESSION("Shutdown", "DeimosProfile-Shutdown.json");
    delete app;
    DM_PROFILE_END_SESSION();
}

//#endif

#endif //ENGINE_ENTRYPOINT_H
