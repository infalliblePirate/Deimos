#include "Deimos.h"
#include "Sandbox2D.h"

#include "Deimos/Renderer/Renderer2D.h"
#include "imgui/imgui.h"

Sandbox2D::Sandbox2D() : m_cameraController(1280 / 720.f, true) {

}

Sandbox2D::~Sandbox2D() {

}

void Sandbox2D::onAttach() {
    Deimos::Renderer2D::init();
}

void Sandbox2D::onDetach() {
}

void Sandbox2D::onUpdate(Deimos::Timestep timestep) {
    m_cameraController.onUpdate(timestep);

    Deimos::RenderCommand::setClearColor({0.3f, 0.2f, 0.8f, 1});
    Deimos::RenderCommand::clear();

    Deimos::Renderer2D::beginScene(m_cameraController.getCamera());
    Deimos::Renderer2D::drawQuad({ 0.f, 0.f }, { 1.f, 1.f }, { 0.8f, 0.2f, 0.3f, 1.f });
    Deimos::Renderer2D::endScene();
    // TODO: add these functions: Shader::setMat4, Shader::setFloat4;
/*
    std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_plainColorShader)->bind();
    std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_plainColorShader)->uploadUniformFloat4("u_color", m_imguiColor);
*/
}

void Sandbox2D::onEvent(Deimos::Event &event) {
    m_cameraController.onEvent(event);
}

void Sandbox2D::onImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", (float *) &m_imguiColor);
    ImGui::End();
}
