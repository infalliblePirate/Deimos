#include "Level.h"
#include "Deimos/Renderer/Renderer2D.h"
#include "Random.h"
#include "imgui/imgui.h"

#include <ctime>

static glm::vec4 HSVtoRGB(const glm::vec3& hsv) {
    float H = hsv.x * 360.0f;
    float S = hsv.y;
    float V = hsv.z;

    float C = S * V;
    float X = C * (1.0f - fabs(fmod(H / 60.0f, 2.0f) - 1.0f));
    float m = V - C;
    float Rs, Gs, Bs;

    if (H >= 0 && H < 60) {
        Rs = C;
        Gs = X;
        Bs = 0;
    } else if (H >= 60 && H < 120) {
        Rs = X;
        Gs = C;
        Bs = 0;
    } else if (H >= 120 && H < 180) {
        Rs = 0;
        Gs = C;
        Bs = X;
    } else if (H >= 180 && H < 240) {
        Rs = 0;
        Gs = X;
        Bs = C;
    } else if (H >= 240 && H < 300) {
        Rs = X;
        Gs = 0;
        Bs = C;
    } else {
        Rs = C;
        Gs = 0;
        Bs = X;
    }

    return { (Rs + m), (Gs + m), (Bs + m), 1.0f };
}


void Level::init(const std::string& path) {
    m_player.loadAssets(std::string(ASSETS_DIR) + "/textures/shipp.png");

    m_triangleTex = Deimos::Texture2D::create(path);
    m_pillars.resize(5);
    for (int i = 0; i < 5; i++) {
        createPillar(i, i * 10);
    }
}

void Level::onRender() {
    // Background
	Deimos::Renderer2D::drawQuad({ m_player.getPosition().x, 0.0f, -0.8f }, { 50.0f, 50.0f }, { 40.f/255.f, 40.f/255.f, 43.f/255.f, 1.0f });

    m_player.onRender();
    glm::vec4 color = HSVtoRGB(m_pillarHSV);

	// Floor and ceiling
	Deimos::Renderer2D::drawQuad({ m_player.getPosition().x,  34.0f }, { 50.0f, 50.0f }, color);
	Deimos::Renderer2D::drawQuad({ m_player.getPosition().x, -34.0f }, { 50.0f, 50.0f }, color);

    //go through each of the pillars and render 'em
    for (int i = 0; i < 5; i++) {
        Deimos::Renderer2D::drawRotatedQuad(m_pillars[i].topPos, m_size, m_triangleTex, glm::radians(180.f), 1, color);
        Deimos::Renderer2D::drawQuad(m_pillars[i].bottomPos, m_size, m_triangleTex, 1, color);
    }
}

void Level::onUpdate(Deimos::Timestep ts) {
    m_player.onUpdate(ts);

    // check for collisions
    if (collisionTest()) {
        gameOver();
        return;
    }

    // recreate pillars when they go out of view
    if (m_player.getPosition().x > m_targetPillar) {
        createPillar(m_targetIndex++ % 5, m_targetPillar + 20.f);
        m_targetPillar += 10.f;
    }

    m_pillarHSV.x += 0.01f * ts;
    if (m_pillarHSV.x > 1.0f) {
        m_pillarHSV.x -= 1.f;
    }
    
}

void Level::createPillar(int index, float offset) {
    Pillar& pillar = m_pillars[index];

    float center = Random::Float() * 4 - 2; // center ranges from -2 to 2
    float gap = Random::Float() * 1.4 + 1.9;
    pillar.topPos = { 6.f + offset, 8 + center + gap / 2, index * 0.1f - 0.5f - 0.05 };
    pillar.bottomPos = { 6.f + offset, -8 + center - gap / 2, index * 0.1f - 0.5f };
}

static bool pointInTri(const glm::vec2& p, const glm::vec2& p0, const glm::vec2& p1, const glm::vec2& p2) {
    float s = p0.y * p2.x - p0.x * p2.y + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y;
	float t = p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x + (p1.x - p0.x) * p.y;

	if ((s < 0) != (t < 0))
		return false;

	float A = -p1.y * p2.x + p0.y * (p2.x - p1.x) + p0.x * (p1.y - p2.y) + p1.x * p2.y;

	return A < 0 ?
		(s <= 0 && s + t >= A) :
		(s >= 0 && s + t <= A);
}

bool Level::collisionTest() {
    if (glm::abs(m_player.getPosition().y) > 8.5f) return true;

    glm::vec4 playerVertecies[] = {
        { -0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f, -0.5f, 0.0f, 1.0f },
		{  0.5f,  0.5f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f } 
    };

    const auto& pos = m_player.getPosition();
    glm::vec4 playerTransformedVerts[4];
    for (int i = 0; i < 4; ++i) {
        playerTransformedVerts[i] = glm::translate(glm::mat4{1.f}, { pos.x, pos.y, 0.f })
            * glm::rotate(glm::mat4{1.f}, glm::radians(m_player.getRotation()), { 0.f, 0.f, 1.f })
            * glm::scale(glm::mat4{1.f}, { 1.f, 9/12.f, 1.0f })
            * playerVertecies[i];
    }

    // each triangle corner is 10% from the texture edge
    glm::vec4 pillarVertices[3] = {
        { -0.5f + 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.5f - 0.1f, -0.5f + 0.1f, 0.0f, 1.0f },
		{  0.0f + 0.0f,  0.5f - 0.1f, 0.0f, 1.0f },
    };

    for (auto& p : m_pillars) {
        glm::vec2 tri[3];

        // top pillars
        for (int i = 0; i < 3; ++i) {
            tri[i] = glm::translate(glm::mat4{1.f}, p.topPos) 
            * glm::rotate(glm::mat4{1.f}, glm::radians(180.f), {0.f, 0.f, 1.f})
            * glm::scale(glm::mat4{1.f}, {m_size.x, m_size.y, 1.f})
            * pillarVertices[i];
        }

        for (auto & vert : playerTransformedVerts) {
            if(pointInTri({vert.x, vert.y}, tri[0], tri[1], tri[2]))
                return true;
        }

        // bottom pillars
        for (int i = 0; i < 3; ++i) {
            tri[i] = glm::translate(glm::mat4{1.f}, p.bottomPos) 
            * glm::scale(glm::mat4{1.f}, {m_size.x, m_size.y, 1.f})
            * pillarVertices[i];
        }

        for (auto & vert : playerTransformedVerts) {
            if(pointInTri({vert.x, vert.y}, tri[0], tri[1], tri[2]))
                return true;
        }
    }


    return false;
}

void Level::gameOver() {
    m_isGameOver = true;
}

void Level::onImGuiRender() {
    m_player.onImGuiRender();
}

void Level::reset() {
    m_pillarHSV = { 0.8f, 0.8f, 0.95f };
    m_isGameOver = false;
    m_targetPillar = 30.f;
    m_targetIndex = 0;
    for (int i = 0; i < 5; i++) {
        createPillar(i, i * 10);
    }
    m_player.reset();
}
