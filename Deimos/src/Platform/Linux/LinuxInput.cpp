#ifdef DM_PLATFORM_LINUX

#include "LinuxInput.h"
#include "GLFW/glfw3.h"
#include "Deimos/Core/Application.h"



namespace Deimos {
    Scope<Input> Input::s_instance = createScope<LinuxInput>();

    bool LinuxInput::isKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool LinuxInput::isMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> LinuxInput::getMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { (float)x, (float)y };
    }

    float LinuxInput::getMouseXImpl() {
        auto[x, y] = getMousePositionImpl();
        return x;
    }

    float LinuxInput::getMouseYImpl() {
        auto[x, y] = getMousePositionImpl();
        return y;
    }
}

#endif
