#pragma once

#include <cmath>
#include <SFML/System.hpp>


namespace Math
{
    template <typename T>
    T distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
    {
        return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
    }


    template <typename T>
    T length(const sf::Vector2<T>& vector)
    {
        return distance(vector, {0, 0});
    }
}