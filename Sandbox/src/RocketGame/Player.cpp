#include "Player.h"
#include "Deimos/Renderer/Renderer2D.h"

#include "Deimos/Events/Event.h"
#include "Deimos/Core/Input.h"
#include "Deimos/Core/KeyCodes.h"

Player::Player() {
    // Flames
    m_flameProps.position = { m_pos.x, m_pos.y };
    m_flameProps.velocity = { -2.f, 1.f };
    m_flameProps.velocityVariation = { 4.f, 2.f };
    m_flameProps.colorBegin =  { 202 / 255.0f, 49 / 255.0f, 49 / 255.0f, 1.0f };
    m_flameProps.colorEnd = { 255/255.f, 255 / 255.0f, 49 / 255.0f , 1.0f };
    m_flameProps.sizeBegin = 0.6f;
    m_flameProps.sizeEnd = 0.f;
    m_flameProps.sizeVariation = 0.3f;
    m_flameProps.lifetime = 3.8f;
}

void Player::onUpdate(Deimos::Timestep ts) {
    if(Deimos::Input::isKeyPressed(DM_KEY_SPACE)) {
        m_vertSpeed = m_enginePower;

        // Flames
        glm::vec2 emissionPoint = { -0.6f, 0.2f };
        glm::vec4 rotated = glm::rotate( glm::mat4{1.f}, getRotation(), {0.f, 0.f, 1.f})
            * glm::vec4(emissionPoint, 0.f, 1.f);
        m_flameProps.position = m_pos + glm::vec3{ rotated.x, rotated.y, 0.0f};
        m_particleSystem.emit(m_flameProps);
    } 

    m_pos.y += m_vertSpeed * ts;
    m_vertSpeed -= m_fallingConstant * ts;
    m_pos.x += 0.1f;

    m_particleSystem.onUpdate(ts);
}

void Player::onRender() {
    Deimos::Renderer2D::drawRotatedQuad(m_pos, {1.f, m_modelRatio}, m_rocketTexture, glm::radians(getRotation()));
    m_particleSystem.onRender();
}

void Player::onImGuiRender() {
}

void Player::loadAssets(const std::string &path) {
    m_rocketTexture = Deimos::Texture2D::create(path);
}

void Player::reset() {
    m_pos = { 0.f, 0.f, -0.6f };
    m_vertSpeed = 0.f;
}
