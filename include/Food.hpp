#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Food
{
public:
    Food(sf::Vector2f position) : position(position) {}
    ~Food() = default;

    inline sf::Vector2f getPosition() const { return position; }
    inline sf::Color getColor() const { return color; }
    inline size_t getHealthBonus() const { return HEALTH_BONUS; }
    inline bool operator==(const Food& other) const { return position == other.position; }// && HEALTH_BONUS == HEALTH_BONUS; }

private:
    sf::Vector2f position;
    sf::Color color = sf::Color::Green;
    static inline const size_t HEALTH_BONUS = 50;
};