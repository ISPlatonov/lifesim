#include "Figures.hpp"
#include <cmath>


Figure::Figure(FigureType type, sf::Vector2f position) : type(type), position(position)
{
    switch (type)
    {
    case FigureType::Point:
        vertices.push_back(sf::Vertex(position, getRandomColor()));
        break;
    case FigureType::Line:
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Figure::FIGURE_SIZE, -Figure::FIGURE_SIZE), getRandomColor()));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE, Figure::FIGURE_SIZE), getRandomColor()));
        break;
    case FigureType::Triangle:
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Figure::FIGURE_SIZE, -Figure::FIGURE_SIZE), getRandomColor()));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE, -Figure::FIGURE_SIZE), getRandomColor()));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(0, Figure::FIGURE_SIZE), getRandomColor()));
        break;
    case FigureType::Rectangle:
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Figure::FIGURE_SIZE, -Figure::FIGURE_SIZE), getRandomColor()));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE, -Figure::FIGURE_SIZE), getRandomColor()));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE, Figure::FIGURE_SIZE), getRandomColor()));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Figure::FIGURE_SIZE, Figure::FIGURE_SIZE), getRandomColor()));
        break;
    case FigureType::Circle:
        {
            double i = 0;
            vertices.push_back(sf::Vertex(position, getRandomColor()));
            vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE * cos(i), Figure::FIGURE_SIZE * sin(i)), vertices.back().color));
            i += PRECISION;
            vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE * cos(i), Figure::FIGURE_SIZE * sin(i)), vertices.back().color));
            for (; i <= 2 * PI + PRECISION;)
            {
                vertices.push_back(sf::Vertex(position, vertices.back().color));
                vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE * cos(i), Figure::FIGURE_SIZE * sin(i)), vertices.back().color));
                i += PRECISION;
                vertices.push_back(sf::Vertex(position + sf::Vector2f(Figure::FIGURE_SIZE * cos(i), Figure::FIGURE_SIZE * sin(i)), vertices.back().color));
            }
        }
        break;
    default:
        break;
    }
}