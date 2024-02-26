#ifndef ENGINE_MOUSEEVENT_H
#define ENGINE_MOUSEEVENT_H

#include "Event.h"

namespace Deimos {

    class DM_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {

        }
        inline float getX() const { return m_mouseX; }
        inline float getY() const { return m_mouseY; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
            return ss.str();
        }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
        EVENT_CLASS_TYPE(MouseMoved)

    private:
        float m_mouseX, m_mouseY;
    };


    class DM_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : m_xOffset(xOffset), m_yOffset(yOffset){

        }
        inline float getXOffset() const { return m_xOffset; }
        inline float getYOffset() const { return m_yOffset; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << getXOffset() << ", " << getYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_xOffset, m_yOffset;
    };

    class DM_API MouseButtonEvent : public Event{
    public:
        MouseButtonEvent(int button) : m_button(button) {

        }

        EVENT_CLASS_CATEGORY(EventCategoryMouseButton | EventCategoryInput)

        inline int getMouseButton() const { return m_button; }

    protected:
        int m_button;
    };

    class DM_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {

        }

        std::string toString() const override{
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class DM_API MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {

        }

        std::string toString() const override {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_button;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

}

#endif //ENGINE_MOUSEEVENT_H
