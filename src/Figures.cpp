#include "Figures.hpp"
#include "Constants.hpp"
#include <cmath>


Figure::Figure(FigureType type, sf::Vector2f position, sf::Color clr) : type(type), position(position), color(clr)
{
    switch (type)
    {
    case FigureType::Point:
        vertices.push_back(sf::Vertex(position, color));
        break;
    case FigureType::Line:
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Constants::Figures::FIGURE_SIZE, -Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE, Constants::Figures::FIGURE_SIZE), color));
        break;
    case FigureType::Male:
    case FigureType::Triangle:
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Constants::Figures::FIGURE_SIZE, -Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE, -Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(0, Constants::Figures::FIGURE_SIZE), color));
        break;
    case FigureType::Female:
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE, Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Constants::Figures::FIGURE_SIZE, Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(0, -Constants::Figures::FIGURE_SIZE), color));
        break;
    case FigureType::Rectangle:
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Constants::Figures::FIGURE_SIZE, -Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE, -Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE, Constants::Figures::FIGURE_SIZE), color));
        vertices.push_back(sf::Vertex(position + sf::Vector2f(-Constants::Figures::FIGURE_SIZE, Constants::Figures::FIGURE_SIZE), color));
        break;
    case FigureType::Circle:
        {
            double i = 0;
            vertices.push_back(sf::Vertex(position, color));
            vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE * cos(i), Constants::Figures::FIGURE_SIZE * sin(i)), vertices.back().color));
            i += Constants::Figures::PRECISION;
            vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE * cos(i), Constants::Figures::FIGURE_SIZE * sin(i)), vertices.back().color));
            for (; i <= 2 * Constants::Figures::PI + Constants::Figures::PRECISION;)
            {
                vertices.push_back(sf::Vertex(position, vertices.back().color));
                vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE * cos(i), Constants::Figures::FIGURE_SIZE * sin(i)), vertices.back().color));
                i += Constants::Figures::PRECISION;
                vertices.push_back(sf::Vertex(position + sf::Vector2f(Constants::Figures::FIGURE_SIZE * cos(i), Constants::Figures::FIGURE_SIZE * sin(i)), vertices.back().color));
            }
        }
        break;
    default:
        break;
    }
}


void Figure::shift(const sf::Vector2f& shift_vector)
{
    for (auto& vertex : vertices)
    {
        vertex.position += shift_vector;
    }
}