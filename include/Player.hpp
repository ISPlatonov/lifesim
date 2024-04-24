#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Food.hpp"
#include <vector>


class Player
{
public:
    Player(sf::Vector2f position);
    ~Player() = default;

    float VIEW_RADIUS = 1500.f;

    std::vector<Food> make_turn(std::vector<Food> foods_around);
    void eat(Food& food);
    inline sf::Vector2f getPosition() const { return position; }
    inline sf::Color getColor() const { return color; }
    inline int getHealth() const { return health; }
    inline bool operator==(const Player& other) const { return position == other.position && health == other.health && color == other.color; }

private:
    void shift(const sf::Vector2f& shift_vector);

    sf::Vector2f position;
    int health = 100;
    //size_t damage = 10;
    sf::Color color = sf::Color(rand() % 256, rand() % 256, rand() % 256);
    float SPEED;
};