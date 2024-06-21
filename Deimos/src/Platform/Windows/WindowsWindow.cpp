#ifdef DM_PLATFORM_WINDOWS

#include "dmpch.h"
#include "WindowsWindow.h"

#include "Deimos/Events/KeyEvent.h"
#include "Deimos/Events/ApplicationEvent.h"
#include "Deimos/Events/MouseEvent.h"
#include "spdlog/details/fmt_helper.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Deimos {
    // static because should only be inited once no matter how many windows
    static uint8_t s_GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char *description) {
        DM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window *Window::create(const WindowProps &props) {
        return new WindowsWindow(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps &props) {
        DM_PROFILE_FUNCTION();

        init(props);
    }

    WindowsWindow::~WindowsWindow() {
        DM_PROFILE_FUNCTION();

        shutdown();
    }

    void WindowsWindow::init(const Deimos::WindowProps &props) {
        DM_PROFILE_FUNCTION();

        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        DM_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (s_GLFWWindowCount == 0) {
            // TODO glfw terminate on system shutdown
            int success = glfwInit();
            DM_CORE_ASSERT(success, "Could not initialize GLFW!");

            glfwSetErrorCallback([](int error, const char *description) {
                DM_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
            });
        }

        {
            glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
            DM_PROFILE_SCOPE("glfwCreateWindow");
            m_window = glfwCreateWindow((int) props.width, (int) props.height, m_data.title.c_str(), nullptr, nullptr);
            ++s_GLFWWindowCount;
        }
        
        m_context = createScope<OpenGLContext>(m_window);
        m_context->init();

        // m_window will store a pointer to user-defined data, which could be later accessed
        glfwSetWindowUserPointer(m_window, &m_data);
        setVSync(true);

        // Set GLFW callbacks
        glfwSetWindowSizeCallback(m_window, [](GLFWwindow *window, int width, int height) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            data.height = height;
            data.width = width;

            WindowResizeEvent event(width, height);
            data.eventCallback(event); // invoke the function onEvent with our event
        });

        glfwSetWindowCloseCallback(m_window, [](GLFWwindow *window) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.eventCallback(event);
        });

        glfwSetKeyCallback(m_window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    KeyPressedEvent event(key, 0);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    KeyReleasedEvent event(key);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_REPEAT: {
                    KeyPressedEvent event(key, 1);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode) {
           WindowData &data = *(WindowData*) glfwGetWindowUserPointer(window) ;

            KeyTypedEvent event(keycode);
            data.eventCallback(event);
        });

        glfwSetMouseButtonCallback(m_window, [](GLFWwindow *window, int button, int action, int mods) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
            switch (action) {
                case GLFW_PRESS: {
                    MouseButtonPressedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
                case GLFW_RELEASE: {
                    MouseButtonReleasedEvent event(button);
                    data.eventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_window, [](GLFWwindow *window, double xOffset, double yOffset) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float) xOffset, (float) yOffset);
            data.eventCallback(event);
        });

        glfwSetCursorPosCallback(m_window, [](GLFWwindow *window, double xPos, double yPos) {
            WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float) xPos, (float) yPos);
            data.eventCallback(event);
        });
    }

    void WindowsWindow::onUpdate() {
        DM_PROFILE_FUNCTION();

        glfwPollEvents(); // processes window events
        m_context->swapBuffers();
    }

    void WindowsWindow::shutdown() {
        DM_PROFILE_FUNCTION();
        
        if(--s_GLFWWindowCount == 0)
            glfwTerminate();

        glfwDestroyWindow(m_window);
    }

    void WindowsWindow::setVSync(bool enabled) {
        DM_PROFILE_FUNCTION();

        if (enabled)
            glfwSwapInterval(1); // sets vertical synchronization with the refresh rate of a monitor
        else
            glfwSwapInterval(0); // disables vertiacl synchronization
        m_data.vSync = enabled;
    }

    bool WindowsWindow::isVSync() const {
        return m_data.vSync;
    }
}
#endif