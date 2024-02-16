#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

#include "Core.h"

namespace Deimos {
    class DM_API Application {
    public:
        Application();
        virtual ~Application();

        void run();
    };

    // tob be defined in client
    Application* createApplication();
}


#endif //ENGINE_APPLICATION_H
