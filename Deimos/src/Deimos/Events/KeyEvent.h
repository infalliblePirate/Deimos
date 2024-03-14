#ifndef ENGINE_KEYEVENT_H
#define ENGINE_KEYEVENT_H

#include "Event.h"

namespace Deimos {
    class DM_API KeyEvent : public Event {
    public:
        inline int getKeyCode() const { return m_keyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(int keycode) : m_keyCode(keycode) {

        }

        int m_keyCode;
    };

    class DM_API KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keyCode, int repeatCount) : KeyEvent(keyCode), m_repeatCount(repeatCount) {

        }

        inline int getRepeatCount() const { return m_repeatCount; }

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_repeatCount;
    };

    class DM_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {

        }

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)

    };

    class DM_API KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(int keycode) : KeyEvent(keycode) {

        }

        std::string toString() const override {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_keyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)

    };
}


#endif //ENGINE_KEYEVENT_H
