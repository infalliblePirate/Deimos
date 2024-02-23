#ifndef ENGINE_APPLICATIONEVENT_H
#define ENGINE_APPLICATIONEVENT_H

#include "Event.h"

namespace Deimos {
    class DM_API WindowResizeEvent : public Event {
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
                : m_height(height), m_width(width) {

        }

        inline unsigned int getHeight() const { return m_height; }
        inline unsigned int getWidth() const { return m_width; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << m_width << ", " << m_height;
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(EventCategoryApplication)
        EVENT_CLASS_TYPE(WindowsResize)

    private:
        unsigned int m_height, m_width;
    };

    class DM_API WindowCloseEvent : public Event {
    public:
        WindowCloseEvent() {

        }

        EVENT_CLASS_TYPE(WindowsClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class DM_API AppTickEvent : public Event {
    public:
        AppTickEvent() {

        }

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class DM_API AppUpdateEvent : public Event {
    public:
        AppUpdateEvent() {

        }

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class DM_API AppRenderEvent : public Event {
    public:
        AppRenderEvent() {

        }

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };
}





#endif //ENGINE_APPLICATIONEVENT_H
