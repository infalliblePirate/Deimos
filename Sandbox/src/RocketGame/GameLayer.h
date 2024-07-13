#pragma once

#include "Deimos.h"
#include "Level.h"

class GameLayer : public Deimos::Layer {
public:
    GameLayer();
    virtual ~GameLayer() = default;

    virtual void onAttach() override;
    virtual void onDetach() override;

    virtual void onUpdate(Deimos::Timestep timestep) override;
    virtual void onEvent(Deimos::Event &event) override;

    virtual void onImGuiRender() override;
private:
    bool onWindowResizeEvent(Deimos::WindowResizeEvent &e);
    bool onMouseButtonPressedEvent(Deimos::MouseButtonEvent &e);
    void createCamera(uint32_t width, uint32_t height);
private:
    enum class State {
        Play = 0, Menu, GameOver
    };
    State m_gameState = State::Menu;
    Deimos::Ref<Deimos::Shader> m_textureShader;
    Deimos::Ref<Deimos::VertexArray> m_vertexArray;

    Deimos::Ref<Deimos::Texture2D> m_triangleTexture;
    Level m_level;
    ImFont* m_font;

    Deimos::Ref<Deimos::OrthographicCamera> m_camera;
};