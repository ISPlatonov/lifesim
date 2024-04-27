#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


enum class ObjectType
{
    None,
    Player,
    Food
};


class Object
{
public:
    Object(const sf::Vector2f& position, const ObjectType& type, const sf::Color& color) : position(position), type(type), color(color) {}
    Object(const Object& other) : position(other.position), type(other.type), color(other.color) {}
    virtual ~Object() = default;

    inline sf::Vector2f getPosition() const { return position; }
    inline ObjectType getType() const { return type; }
    inline sf::Color getColor() const { return color; }
    virtual bool operator==(const Object& other) const { return position == other.position && color == other.color; }

protected:
    sf::Vector2f position;
    ObjectType type;
    sf::Color color;
};