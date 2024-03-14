#include "dmpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "Deimos/Application.h"

// Temporary
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Deimos {
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer") {
    }

    ImGuiLayer::~ImGuiLayer() {
    }

    void ImGuiLayer::onAttach() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // TEMPORARY: should eventually use Hazel key codes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::onDetach() {
    }

    void ImGuiLayer::onUpdate() {
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::get();
        io.DisplaySize = ImVec2(app.getWindow().getWidth(), app.getWindow().getHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
        m_time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::onEvent(Event &event) {
        EventDispatcher dispatcher(event);
        dispatcher.dispatch<MouseButtonPressedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::onMouseButtonPressedEvent));
        dispatcher.dispatch<MouseButtonReleasedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::onMouseButtonReleasedEvent));
        dispatcher.dispatch<MouseScrolledEvent>(DM_BIND_EVENT_FN(ImGuiLayer::onMouseScrolledEvent));
        dispatcher.dispatch<MouseMovedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::onMouseMovedEvent));
        dispatcher.dispatch<KeyPressedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::onKeyPressedEvent));
        dispatcher.dispatch<KeyReleasedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::onKeyReleasedEvent));
        dispatcher.dispatch<KeyTypedEvent>(DM_BIND_EVENT_FN(ImGuiLayer::onKeyTypedEvent));
    }

    bool ImGuiLayer::onKeyPressedEvent(KeyPressedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.getKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
        return false;
    }

    bool ImGuiLayer::onKeyReleasedEvent(KeyReleasedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.KeysDown[e.getKeyCode()] =  false;

        return false;
    }

    bool ImGuiLayer::onMouseMovedEvent(MouseMovedEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.MousePos = ImVec2(e.getX(), e.getY());

        return false;
    }

    bool ImGuiLayer::onMouseScrolledEvent(MouseScrolledEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.MouseWheel = e.getYOffset();
        io.MouseWheelH = e.getXOffset();

        return false;
    }

    bool ImGuiLayer::onMouseButtonPressedEvent(MouseButtonPressedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        if (e.getMouseButton() >= 0 && e.getMouseButton() < ImGuiMouseButton_COUNT)
            io.AddMouseButtonEvent(e.getMouseButton(), true);

        return false;
    }

    bool ImGuiLayer::onMouseButtonReleasedEvent(MouseButtonReleasedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        if (e.getMouseButton() >= 0 && e.getMouseButton() < ImGuiMouseButton_COUNT)
            io.AddMouseButtonEvent(e.getMouseButton(), false);

        return false;
    }

    bool ImGuiLayer::onWindowResizeEvent(WindowResizeEvent &e) {
        ImGuiIO &io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.getWidth(), e.getHeight());
        io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
        glViewport(0,0, e.getWidth(), e.getHeight());

        return false;
    }

    bool ImGuiLayer::onKeyTypedEvent(KeyTypedEvent &e) {
        ImGuiIO& io = ImGui::GetIO();
        int keycode = e.getKeyCode();
        if(keycode > 0 && keycode < 0x10000)
            io.AddInputCharacter((unsigned int)keycode);

        return false;
    }

}
