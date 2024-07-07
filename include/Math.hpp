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
        float dx = cos(player_angle);
        float dy = sin(player_angle);
        float a = 1;
        float b = -2 * (player_position.x * dx + player_position.y * dy);
        float c = player_position.x * player_position.x + player_position.y * player_position.y - Constants::Figures::FIGURE_SIZE * Constants::Figures::FIGURE_SIZE;
        float d = b * b - 4 * a * c;
        //std::cout << "d = " << d << std::endl;
        if (d < 0) {
            return false;
        } else if (d == 0) {
            float t = -b / (2 * a);
            // check if the intersection point is in front of the player
            return t >= 0 && ((food_position.x - player_position.x) >= 0) == (dx >= 0) && ((food_position.y - player_position.y) >= 0) == (dy >= 0);
        } else {
            float t1 = (-b + sqrt(d)) / (2 * a);
            float t2 = (-b - sqrt(d)) / (2 * a);
            // check if the intersection point is in front of the player
            //std::cout << "t1 = " << t1 << ", t2 = " << t2 << ", angle = " << player_angle << std::endl;
            //std::cout << (((t1 >= 0 || t2 >= 0) && ((food_position.x - player_position.x) >= 0) == (dx >= 0) && ((food_position.y - player_position.y) >= 0) == (dy >= 0)) ? "true" : "false") << std::endl;
            return (t1 >= 0 || t2 >= 0) && ((food_position.x - player_position.x) >= 0) == (dx >= 0) && ((food_position.y - player_position.y) >= 0) == (dy >= 0);
        }
    }
}