#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>


enum class FigureType
{
    Point,
    Line,
    Triangle,
    Rectangle,
    Circle,
    Male,
    Female
};


class Figure
{
public:
    Figure(FigureType type, sf::Vector2f position, sf::Color color = getRandomColor());
    ~Figure() = default;

    inline std::vector<sf::Vertex> getVertices() const { return vertices; }
    void shift(const sf::Vector2f& shift_vector);

protected:
    static inline const sf::Color getRandomColor()
    {
        return sf::Color(rand() % 256, rand() % 256, rand() % 256);
    }

    sf::Vector2f position;
    FigureType type;
    std::vector<sf::Vertex> vertices;
    sf::Color color;
};