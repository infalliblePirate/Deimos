#ifdef DM_PLATFORM_LINUX


#include "dmpch.h"
#include "LinuxWindow.h"

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
        return new LinuxWindow(props);
    }

    LinuxWindow::LinuxWindow(const WindowProps &props) {
        DM_PROFILE_FUNCTION();

        init(props);
    }

    LinuxWindow::~LinuxWindow() {
        DM_PROFILE_FUNCTION();

        shutdown();
    }

    void LinuxWindow::init(const Deimos::WindowProps &props) {
        DM_PROFILE_FUNCTION();

        m_data.title = props.title;
        m_data.width = props.width;
        m_data.height = props.height;

        DM_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

        if (s_GLFWWindowCount == 0) {
            DM_PROFILE_SCOPE("glfwInit");
            // TODO glfw terminate on system shutdown
            int success = glfwInit();
            DM_CORE_ASSERT(success, "Could not initialize GLFW!");
           // wl_subsurface_set_position(static_cast<wl_subsurface*>(m_window), 0, 0);

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

    void LinuxWindow::onUpdate() {
        DM_PROFILE_FUNCTION();

        glfwPollEvents(); // processes window events
        m_context->swapBuffers();
    }

    void LinuxWindow::shutdown() {
        DM_PROFILE_FUNCTION();

        glfwDestroyWindow(m_window);

        if(--s_GLFWWindowCount == 0) 
            glfwTerminate();
    }

    void LinuxWindow::setVSync(bool enabled) {
        DM_PROFILE_FUNCTION();

        if (enabled)
            glfwSwapInterval(1); // sets vertical synchronization with the refresh rate of a monitor
        else
            glfwSwapInterval(0); // disables vertiacl synchronization
        m_data.vSync = enabled;
    }

    bool LinuxWindow::isVSync() const {
        return m_data.vSync;
    }
}

#endif
