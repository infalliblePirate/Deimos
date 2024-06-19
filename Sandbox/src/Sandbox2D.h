#ifndef ENGINE_SANDBOX2D_H
#define ENGINE_SANDBOX2D_H

#include "Deimos.h"

class Sandbox2D : public Deimos::Layer {
public:
    Sandbox2D();
    ~Sandbox2D();

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(Deimos::Timestep timestep) override;
    virtual void onEvent(Deimos::Event &event);

    virtual void onImGuiRender() override;
private:
    glm::vec4 m_imguiColor{1.f, 1.f, 1.f, 1.f};

    Deimos::Ref<Deimos::Shader> m_plainColorShader;
    Deimos::Ref<Deimos::Shader> m_textureShader;

    Deimos::Ref<Deimos::VertexArray> m_squareVA;

    Deimos::Ref<Deimos::Texture2D> m_girlTexture;

    Deimos::OrthographicCameraController m_cameraController;
    glm::vec3 m_cameraPosition{0.f};

    struct ProfileResult {
        const char* name;
        float time;
    };
    std::vector<ProfileResult> m_profileResults;
};


#endif //ENGINE_SANDBOX2D_H
