#pragma once

#include <vector>

#include "Player.h"

#include "Deimos/Core/Core.h"
#include "Deimos/Core/Timestep.h"

#include "Deimos/Renderer/Texture.h"
#include <glm/glm/gtc/matrix_transform.hpp>

#include "Deimos/ImGui/ImGuiLayer.h"

struct Pillar {
    glm::vec3 topPos = {};
    glm::vec3 bottomPos = {};
    glm::vec2 size = { 5.f, 8.f };
};

class Level {
public:
    void init(const std::string& path);

    void onUpdate(Deimos::Timestep ts);
    void onRender();
    void onImGuiRender();

    void reset();
    inline bool isGameOver() { return m_isGameOver; }
    inline Player& getPlayer() { return m_player; }
private:
    void createPillar(int index, float offset); 
    bool collisionTest();
    glm::vec4 getRandomColor();
    void gameOver();
private:
    Player m_player;

    Deimos::Ref<Deimos::Texture2D> m_triangleTex;
    std::vector<Pillar> m_pillars;
    float m_targetPillar = 30.f;
    int m_targetIndex = 0;
    glm::vec3 m_pillarHSV = { 0.8f, 0.8f, 0.95f };

    glm::vec4 m_playerTransformedVerts[4];
    glm::vec2 m_size = { 15.0f, 20.0f };

    bool m_isGameOver = false;
};