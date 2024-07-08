#pragma once

#include "Object.hpp"


namespace Event
{
    enum class Type
    {
        Move,
        Eat,
        Damage,
        Sex
    };


    class Event
    {
    public:
        Event(Type type, std::shared_ptr<Object> object_ptr) : type(type) { object = object_ptr; }
        Event(const Event& other) : type(other.type), object(other.object) {}
        virtual ~Event() = default;

        inline Type getType() const { return type; }
        inline std::shared_ptr<Object> getObjectPtr() { return object; }

    private:
        Type type;
        std::shared_ptr<Object> object;
    };
}