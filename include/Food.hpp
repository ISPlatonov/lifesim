#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.hpp"


class Food : public Object
{
public:
    Food(const sf::Vector2f& position) : Object(position, ObjectType::Food, sf::Color::Green) {}
    Food (const Food& other) : Object(other), health_bonus(other.health_bonus) {}
    ~Food() = default;

    inline int getHealthBonus() const { return health_bonus; }
    inline int getSatietyBonus() const { return satiety_bonus; }
    inline bool operator==(const Food& other) const { return position == other.position && health_bonus == other.health_bonus; }
    inline Food& operator=(const Food& other) { position = other.position; health_bonus = other.health_bonus; return *this; }

private:
    int health_bonus = 10;
    int satiety_bonus = 200;
};