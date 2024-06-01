#ifndef ENGINE_TIMESTEP_H
#define ENGINE_TIMESTEP_H

namespace Deimos {
    class Timestep {
    public:
        Timestep(float time = 0.f) : m_time(time) {
        }

        float getSeconds() const { return m_time; }
        float getMilliseconds() const { return m_time * 1000.f; }

        operator float const () {
            return m_time;
        }
    private:
        float m_time;
    };
}

#endif //ENGINE_TIMESTEP_H
