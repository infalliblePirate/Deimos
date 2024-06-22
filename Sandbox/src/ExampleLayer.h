#ifndef ENGINE_EXAMPLELAYER_H
#define ENGINE_EXAMPLELAYER_H

#include "Deimos.h"

class ExampleLayer : public Deimos::Layer {
public:
    ExampleLayer();
    virtual ~ExampleLayer() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(Deimos::Timestep timestep) override;
    virtual void onEvent(Deimos::Event &event) override;

    virtual void onImGuiRender() override;
private:
    Deimos::Ref<Deimos::Shader> m_shader;
    Deimos::Ref<Deimos::Shader> m_plainColorShader;
    Deimos::Ref<Deimos::Shader> m_TextureShader;

    Deimos::Ref<Deimos::VertexArray> m_vertexArray;
    Deimos::Ref<Deimos::VertexArray> m_squareVA;

    Deimos::Ref<Deimos::Texture2D> m_texture, m_texture2;

    Deimos::OrthographicCameraController m_cameraController;

    glm::vec4 m_color{1.f, 1.f, 1.0f, 1.0f};
};

#endif // ENGINE_EXAMPLELAYER_H