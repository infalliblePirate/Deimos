#include "GameLayer.h"
#include "Random.h"
#include "Deimos/Core/Core.h"

#include <glm/glm/gtc/matrix_transform.hpp>

using namespace Deimos;

GameLayer::GameLayer() : Layer("RocketGameLayer") {
    auto& window = Application::get().getWindow();
    createCamera(window.getWidth(), window.getHeight());
    float aspectRatio = (float)window.getWidth() / window.getHeight();
}

void GameLayer::onAttach() {
    Renderer2D::init();
    m_level.init(std::string(ASSETS_DIR) + "/textures/Triangle.png");
    m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF((std::string(ASSETS_DIR) + "/OpenSans-Regular.ttf").c_str(), 120.f);
}

void GameLayer::onDetach() {

}

void GameLayer::onUpdate(Deimos::Timestep timestep) {
    RenderCommand::setClearColor({ 1.f, 1.f, 1.f, 1.f });
    RenderCommand::clear();
    m_camera->setPosition({m_level.getPlayer().getPosition()});

    if (m_level.isGameOver())
        m_gameState = State::GameOver;
    
    if (m_gameState == State::Play)
        m_level.onUpdate(timestep);

    Renderer2D::beginScene(*m_camera);
    m_level.onRender();
    Renderer2D::endScene();
}

void GameLayer::onEvent(Deimos::Event &event) {
    EventDispatcher dispatcher(event);
    dispatcher.dispatch<WindowResizeEvent>(DM_BIND_EVENT_FN(GameLayer::onWindowResizeEvent));
    dispatcher.dispatch<MouseButtonPressedEvent>(DM_BIND_EVENT_FN(GameLayer::onMouseButtonPressedEvent));
}

void GameLayer::onImGuiRender() {
    ImDrawList* draw_list = ImGui::GetBackgroundDrawList();
    auto pos = ImGui::GetWindowPos();
    auto width = Application::get().getWindow().getWidth();
    auto height = Application::get().getWindow().getHeight(); 
    switch (m_gameState) {
        case State::Menu: {
        const char* text = "Hit that space to fly, and mouse to relaunch!";
        auto textSize = ImGui::CalcTextSize(text);
        pos.x = (width - textSize.x) * 0.5f + 300; 
        pos.y = (height - textSize.y) * 0.5f - 200.0f;
        draw_list->AddText(m_font, 80.0f, pos, 0xffffffff, text);
        break;
        }
        case State::Play: {
            m_level.onImGuiRender();
            uint32_t playerScore = m_level.getPlayer().getScore();
            std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
            auto textSize = ImGui::CalcTextSize(scoreStr.c_str());
            pos.x = 200.0f;
			pos.y = 200.0f; 
            draw_list->AddText(m_font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
            break;
        }
        case State::GameOver: {
            const char* gameOverText = "Yo! You lost! You did otherwordly bad...";
            auto textSize = ImGui::CalcTextSize(gameOverText);
            pos.x = (width - textSize.x) * 0.5f + 280;
            pos.y = (height - textSize.y) * 0.5f - 200.0f; 
            draw_list->AddText(m_font, 80.0f, pos, 0xffffffff, gameOverText);
            
            uint32_t playerScore = m_level.getPlayer().getScore();
            std::string scoreStr = std::string("Score: ") + std::to_string(playerScore);
            auto scoreTextSize = ImGui::CalcTextSize(scoreStr.c_str());
            pos.x = 200.0f;
			pos.y = 200.0f;
            draw_list->AddText(m_font, 48.0f, pos, 0xffffffff, scoreStr.c_str());
            break;
        }

    }
    
}

bool GameLayer::onWindowResizeEvent(Deimos::WindowResizeEvent &e) {
    createCamera(e.getWidth(), e.getHeight());
    return false;
}

bool GameLayer::onMouseButtonPressedEvent(Deimos::MouseButtonEvent &e) {
    m_level.reset();
    m_gameState = State::Play;
    return true;
}

void GameLayer::createCamera(uint32_t width, uint32_t height) {
    float aspectRatio = (float)width/ height;
    float camWidth = 6.f;
    m_camera = createScope<OrthographicCamera>( -camWidth * aspectRatio, camWidth * aspectRatio, -camWidth, camWidth);
}
