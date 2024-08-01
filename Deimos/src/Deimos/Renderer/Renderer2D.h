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

        // Line with color
        static void drawLine(const glm::vec2 &start, const glm::vec2 &end, float thickness, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawLine(const glm::vec3 &start, const glm::vec3 &end, float thickness, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});

        // Quad with color
        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});

        // Quad with texture
        static void drawQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture>& texture, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec2 &position, const glm::vec2 &size, const Ref<Texture>& texture, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const Ref<Texture>& texture, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});

        // Triangle with color
        static void drawTriangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawTriangle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedTriangle(const glm::vec2 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawRotatedTriangle(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});

        // Circle with color
        static void drawCircle(const glm::vec2 &position, float radius, int vCount, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
        static void drawCircle(const glm::vec3 &position, float radius, int vCount, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});

        // Oval with color
        static void drawOval(const glm::vec2 &center, float a, float b, float rotation, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4 &tintColor = glm::vec4{1.f});
        static void drawOval(const glm::vec3 &center, float a, float b, float rotation, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4 &tintColor = glm::vec4{1.f});

        // Polygon with color
        static void drawPolygon(const glm::vec3 *vertices, int vCount, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});

        // Quadratic bezier curve
        static void drawBezier(const glm::vec3 &anchor1, const glm::vec3 &control, const glm::vec3 &anchor2, const glm::vec4 &color, float tilingFactor = 1.f, const glm::vec4& tintColor = glm::vec4{1.f});
    };
}

#endif //ENGINE_RENDERER2D_H
