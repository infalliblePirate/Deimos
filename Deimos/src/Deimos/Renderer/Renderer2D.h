#ifndef ENGINE_RENDERER2D_H
#define ENGINE_RENDERER2D_H

#include "OrthographicCamera.h"
#include "Texture.h"

namespace Deimos {
    class Renderer2D {
    public:
        static void init();
        static void shutdown();

        static void beginScene(const OrthographicCamera &camera);
        static void endScene();

        // with color
        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});

        // with texture
        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture>& texture, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture>& texture, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
    };
}

#endif //ENGINE_RENDERER2D_H
