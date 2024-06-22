#include "dmpch.h"

#include "Deimos.h"
#include "Sandbox2D.h"

#include "Deimos/Renderer/Renderer2D.h"
#include "imgui/imgui.h"
#include "Deimos/Renderer/Texture.h"

Sandbox2D::Sandbox2D() : m_cameraController(1280 / 720.f, true) {

}

void Sandbox2D::onAttach() {
    DM_PROFILE_FUNCTION();

    Deimos::Renderer2D::init();
    m_girlTexture = Deimos::Texture2D::create(std::string(ASSETS_DIR) + "/textures/go.jpeg");
}

void Sandbox2D::onDetach() {
    DM_PROFILE_FUNCTION();
}

void Sandbox2D::onUpdate(Deimos::Timestep timestep) {
    DM_PROFILE_FUNCTION()

    {
        DM_PROFILE_SCOPE("CameraController::onUpdate");
        m_cameraController.onUpdate(timestep);
    }

    {
        DM_PROFILE_SCOPE("Renderer Prep");
        Deimos::RenderCommand::setClearColor({0.3f, 0.2f, 0.8f, 1});
        Deimos::RenderCommand::clear();
    }

    {
        DM_PROFILE_SCOPE("Renderer Draw");
        Deimos::Renderer2D::beginScene(m_cameraController.getCamera());
        Deimos::Renderer2D::drawQuad({1.f, 1.f}, {1.f, 1.f}, m_girlTexture);
        Deimos::Renderer2D::drawQuad({ 0.f, 0.f, -0.1f }, { 10.f, 10.f }, { 0.4f, 0.5f, 0.6f, 1.f });
        Deimos::Renderer2D::endScene();
    }
}

void Sandbox2D::onEvent(Deimos::Event &event) {
    m_cameraController.onEvent(event);
}

void Sandbox2D::onImGuiRender() {
    DM_PROFILE_FUNCTION();
        
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", (float *) &m_imguiColor);
    for(auto &result : m_profileResults) {
        char label[50];
        strcpy(label, "%.3fms ");
        strcat(label, result.name);
        ImGui::Text(label, result.time);
    }
    m_profileResults.clear();
    ImGui::End();
}
