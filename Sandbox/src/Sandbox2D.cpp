#include "Deimos.h"
#include "Sandbox2D.h"
#include "imgui/imgui.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/glm/gtc/matrix_transform.hpp>

Sandbox2D::Sandbox2D() : m_cameraController(1280 / 720.f, true) {
    m_squareVA = Deimos::VertexArray::create();
    float squareVertices[3 * 4] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,};

    Deimos::Ref<Deimos::VertexBuffer> squareVB;
    squareVB = Deimos::VertexBuffer::create(squareVertices, sizeof(squareVertices));
    squareVB->setLayout(
            {
                    {Deimos::ShaderDataType::Float3, "a_position"},
            });
    m_squareVA->addVertexBuffer(squareVB);

    unsigned int squareIndices[6] = {0, 1, 2, 2, 3, 0};

    Deimos::Ref<Deimos::IndexBuffer> squareIB;
    squareIB = Deimos::IndexBuffer::create(squareIndices, sizeof(squareIndices) / sizeof(unsigned int));

    m_squareVA->setIndexBuffer(squareIB);
    m_plainColorShader = Deimos::Shader::create(std::string(ASSETS_DIR) + "/shaders/PlainColor.glsl");
}

Sandbox2D::~Sandbox2D() {

}

void Sandbox2D::onAttach() {
}

void Sandbox2D::onDetach() {
}

void Sandbox2D::onUpdate(Deimos::Timestep timestep) {
    m_cameraController.onUpdate(timestep);

    Deimos::RenderCommand::setClearColor({0.3f, 0.2f, 0.8f, 1});
    Deimos::RenderCommand::clear();

    Deimos::Renderer::beginScene(m_cameraController.getCamera());

    std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_plainColorShader)->bind();
    std::dynamic_pointer_cast<Deimos::OpenGLShader>(m_plainColorShader)->uploadUniformFloat4("u_color", m_imguiColor);

    Deimos::Renderer::submit(m_plainColorShader, m_squareVA);

    Deimos::Renderer::endScene();
}

void Sandbox2D::onEvent(Deimos::Event &event) {
    m_cameraController.onEvent(event);
}

void Sandbox2D::onImGuiRender() {
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square color", (float *) &m_imguiColor);
    ImGui::End();
}
