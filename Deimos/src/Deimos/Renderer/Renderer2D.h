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

        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color);
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);

        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture>& texture);
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture>& texture);
    };
}

#endif //ENGINE_RENDERER2D_H
