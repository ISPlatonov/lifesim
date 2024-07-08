#pragma once

#include <cmath>
#include <iostream>
#include <SFML/System.hpp>
#include "Constants.hpp"


namespace Math
{
    template <typename T>
    inline T distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
    {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }


    template <typename T>
    inline T length(const sf::Vector2<T>& vector)
    {
        return distance(vector, {0, 0});
    }


    // Math::in_front(player.getPosition(), player.getAngle(), food.getPosition())
    inline bool in_front(const sf::Vector2f& player_position, float player_angle, const sf::Vector2f& food_position)
    {
        // check for line from player to food intersection with circle of FIGURE_SIZE
        // (x - x0)^2 + (y - y0)^2 = r^2
        // (x - xf)^2 + (tan(angle) * (x - xp) - yf + yp)^2 <= FIGURE_SIZE^2
        bool side = ((food_position.x - player_position.x) >= 0) == (cos(player_angle) >= 0) && ((food_position.y - player_position.y) >= 0) == (sin(player_angle) >= 0);
        bool intersection = std::pow(food_position.x - food_position.x, 2) + std::pow(tan(player_angle) * (food_position.x - player_position.x) - food_position.y + player_position.y, 2) <= std::pow(Constants::Figures::FIGURE_SIZE, 2);
        return side && intersection;
    }
}