#include "ParticleSystem.h"

#include "Random.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm/gtx/compatibility.hpp>

ParticleSystem::ParticleSystem() {
    m_particlePool.resize(1000);
}

void ParticleSystem::emit(const ParticleProps& particleProps) {
    Particle& particle = m_particlePool[m_poolIndex];
    particle.active = true;
    particle.position = particleProps.position;
    particle.rotation = Random::Float() * 2.f * glm::pi<float>();

    // Velocity
    particle.velocity = particleProps.velocity; // fetch velocity
    particle.velocity.x += particleProps.velocityVariation.x * (Random::Float() - 0.5f); // update velocity
    particle.velocity.y += particleProps.velocityVariation.y * (Random::Float() - 0.5f);

    // Color
    particle.colorBegin = particleProps.colorBegin;
    particle.colorEnd = particleProps.colorEnd;

    // Size
    particle.sizeBegin = particleProps.sizeBegin + particleProps.sizeVariation * (Random::Float() - 0.5f);
    particle.sizeEnd = particleProps.sizeEnd;

    // Life
    particle.lifetime = particleProps.lifetime;
    particle.lifeRemaining = particleProps.lifetime;

    m_poolIndex = --m_poolIndex % m_particlePool.size();
}

void ParticleSystem::onUpdate(Deimos::Timestep ts) {
    for (auto& particle : m_particlePool) {
        if (!particle.active)
            continue;

        if (particle.lifeRemaining <= 0.f) {
            particle.active = false;
            continue;
        }

        particle.lifeRemaining -= ts;
        particle.position += particle.velocity * (float)ts * 0.3f;
        particle.rotation += 0.01f * ts;
    }
}

void ParticleSystem::onRender() {
    for (auto& particle : m_particlePool) {
        if (!particle.active)
            continue;
        
        // to make fading effect for particles
        float life = particle.lifeRemaining / particle.lifetime; // weight from 0 to 1
        glm::vec4 color = glm::lerp(particle.colorEnd, particle.colorBegin, life);

        float size = glm::lerp(particle.sizeEnd, particle.sizeBegin, life);
        Deimos::Renderer2D::drawRotatedQuad({ particle.position.x, particle.position.y, -0.59 }, { size, size }, color, particle.rotation);
    }
}
