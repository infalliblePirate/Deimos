#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Deimos/Application.h"

namespace Deimos {
    Input* Input::s_instance = new WindowsInput();

    bool WindowsInput::isKeyPressedImpl(int keycode) {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::isMouseButtonPressedImpl(int button) {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::getMousePositionImpl() {
        auto window = static_cast<GLFWwindow*>(Application::get().getWindow().getNativeWindow());
        double x, y;
        glfwGetCursorPos(window, &x, &y);

        return { (float)x, (float)y };
    }

    float WindowsInput::getMouseXImpl() {
        auto[x, y] = getMousePositionImpl();
        return x;
    }

    float WindowsInput::getMouseYImpl() {
        auto[x, y] = getMousePositionImpl();
        return y;
    }
}
