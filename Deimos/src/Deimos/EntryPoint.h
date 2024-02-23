#ifndef ENGINE_ENTRYPOINT_H
#define ENGINE_ENTRYPOINT_H

#include "Log.h"

#ifdef DM_PLATFORM_WINDOWS

extern Deimos::Application* Deimos::createApplication();

int main(int argc, char **argv) {
    Deimos::Log::init();
    //DM_CORE_WARN("I am warning you");
    DM_CRITICAL("Something went wrong (not really)");

    auto app = Deimos::createApplication();
    app->run();
    delete app;
}

#endif

#endif //ENGINE_ENTRYPOINT_H
