#ifndef ENGINE_EVENT_H
#define ENGINE_EVENT_H

#include "dmpch.h"
#include "Deimos/Core/Core.h"
#include "../vendor/spdlog/include/spdlog/fmt/bundled/format.h" // used to define printable custom data

namespace Deimos {

    enum class EventType {
        None = 0,
        WindowsClose, WindowsResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // used bits because one event can be in multiple categories
    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    // used by derived classes
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
        virtual EventType getEventType() const override { return getStaticType(); }\
        virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

    class DM_API Event {
        friend class EventDispatcher;

    public:
        virtual EventType getEventType() const = 0;

        virtual const char *getName() const = 0;

        virtual int getCategoryFlags() const = 0;

        virtual std::string toString() const { return getName(); }

        inline bool isInCategory(EventCategory category) {
            return getCategoryFlags() & category;
        }

        bool handled = false;
    };

    class EventDispatcher {
        template<typename T>
        using eventFn = std::function<bool(T &)>;
    public:
        EventDispatcher(Event &event) : m_event(event) { // create a dispatcher with an occurred event

        }

        template<typename T>
        bool dispatch(eventFn<T> func) { // accepts callable entities
            if (m_event.getEventType() == T::getStaticType()) {
                m_event.handled = func(*(T*) &m_event); // casts from general Event (m_event) to T (example: onWindowCLose)
                return true;
            }
            return false;
        }

    private:
        Event &m_event;
    };

    // defines how to print custom data types
    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.toString();
    }

}

#endif //ENGINE_EVENT_H
