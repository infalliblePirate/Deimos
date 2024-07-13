#pragma once

#include "Deimos.h"

// are user-defined properties
struct ParticleProps {
    glm::vec2 position;
    glm::vec2 velocity, velocityVariation;
    glm::vec4 colorBegin, colorEnd;
    float sizeBegin, sizeEnd, sizeVariation;
    float lifetime = 1.f;
};

class ParticleSystem {
public:
    ParticleSystem();

    void emit(const ParticleProps& particleProps);

    void onUpdate(Deimos::Timestep ts);
    void onRender();
private:
    struct Particle {
        glm::vec2 position;
        glm::vec2 velocity;
        glm::vec4 colorBegin, colorEnd;

        float rotation = 0.f;
        float sizeBegin, sizeEnd;

        float lifetime = 1.f;
        float lifeRemaining = 0.f;

        bool active = false;
    };
    std::vector<Particle> m_particlePool;
    uint32_t m_poolIndex = 999;
};