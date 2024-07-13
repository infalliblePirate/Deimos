#pragma once

#include "Deimos/Core/Core.h"
#include "Deimos/Core/Timestep.h"

#include "Deimos/Events/Event.h"
#include "Deimos/Events/KeyEvent.h"

#include "Deimos/Renderer/Texture.h"
#include "ParticleSystem.h"
#include <glm/glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"

class Player {
public:
    Player();
    ~Player() = default;

    void onUpdate(Deimos::Timestep ts);
    void onRender();
    void onImGuiRender();

    void loadAssets(const std::string& path);
    void reset();

    float getRotation() { return m_vertSpeed * 5.f - 90.f; }
    glm::vec3 getPosition() { return m_pos; }
    inline uint32_t getScore() { return (m_pos.x + 6) / 10; }
private:
    Deimos::Ref<Deimos::Texture2D> m_rocketTexture;
    float m_modelRatio = (float)12. / 9;
    glm::vec3 m_pos{ 0.f, 0.f, -0.6f };

    float m_enginePower = 0.5f;
    const float m_fallingConstant = 0.4f;
    float m_vertSpeed = 0.f;

    ParticleSystem m_particleSystem;
    ParticleProps m_flameProps;
};