#ifndef ENGINE_ENTRYPOINT_H
#define ENGINE_ENTRYPOINT_H

#ifdef DM_PLATFORM_WINDOWS

extern Deimos::Application* Deimos::createApplication();

int main(int argc, char **argv) {
    auto app = Deimos::createApplication();
    app->run();
    delete app;
}

#endif

#endif //ENGINE_ENTRYPOINT_H
