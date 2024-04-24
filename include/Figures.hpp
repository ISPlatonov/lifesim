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
    Circle
};


class Figure
{
public:
    Figure(FigureType type, sf::Vector2f position);
    //virtual ~Figure() = default;
    ~Figure() = default;

    //virtual sf::VertexArray getDrawable() const = 0;
    inline std::vector<sf::Vertex> getVertices() const { return vertices; }

protected:
    static inline const sf::Color getRandomColor()
    {
        return sf::Color(rand() % 256, rand() % 256, rand() % 256);
    }

    sf::Vector2f position;
    FigureType type;
    std::vector<sf::Vertex> vertices;
    static inline const float FIGURE_SIZE = 100;
    static inline const double PRECISION = 0.1;
    static inline const double PI = 3.14159265358979323846;
};