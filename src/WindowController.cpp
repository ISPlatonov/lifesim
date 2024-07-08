#include "WindowController.hpp"
#include "Figures.hpp"
#include "Constants.hpp"
#include <boost/asio.hpp>
#include <boost/thread.hpp>


sf::RenderWindow WindowController::window(sf::VideoMode(Constants::WIDTH, Constants::HEIGHT), WindowController::TITLE);
sf::VertexBuffer WindowController::vertex_buffer(sf::PrimitiveType::Triangles, sf::VertexBuffer::Static);


int WindowController::Run()
{
    boost::asio::io_service::work work(brain.get_io_service());
    while (window.isOpen())
    {
        event_handler(window);
        make_turn();

        window.clear(WindowController::BACKGROUND_COLOR);

        WindowController::draw();

        window.display();
    }
    return 0;
}


void WindowController::make_turn()
{
    if (is_playing)
    {
        figures.clear();
        brain.make_turn(figures);
        vertices.clear();
        for (auto& figure : figures)
        {
            for (auto& vertex : figure.getVertices())
            {
                vertices.push_back(vertex);
            }
        }
        vertex_buffer.create(vertices.size());
        vertex_buffer.update(vertices.data());
    }
}


void WindowController::event_handler(sf::RenderWindow &window)
{
    static sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            if (is_dragging)
            {
                figures.back().shift(sf::Vector2f(event.mouseMove.x, event.mouseMove.y) - staged_mouse_position);
                staged_mouse_position = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
                vertices.clear();
                for (auto& figure : figures)
                {
                    for (auto& vertex : figure.getVertices())
                    {
                        vertices.push_back(vertex);
                    }
                }
                vertex_buffer.create(vertices.size());
                vertex_buffer.update(vertices.data());
            }
            break;
        case sf::Event::MouseButtonPressed:
            switch (event.mouseButton.button)
            {
            case sf::Mouse::Left:
                addDrawable();
                break;
            case sf::Mouse::Right:
                if (!is_dragging)
                {
                    is_dragging = true;
                    staged_mouse_position = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                }
                break;
            default:
                break;
            }
            break;
        case sf::Event::MouseButtonReleased:
            switch (event.mouseButton.button)
            {
                case sf::Mouse::Right:
                    is_dragging = false;
                    break;
                default:
                    break;
            }
            break;
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
                case sf::Keyboard::Space:
                    is_playing = !is_playing;
                    break;
                default:
                    break;
            }
            break;
        case sf::Event::KeyReleased:
            switch (event.key.code)
            {
                case sf::Keyboard::Num1:
                    current_figure = FigureType::Point;
                    vertex_buffer = sf::VertexBuffer(sf::PrimitiveType::Triangles);
                    WindowController::TITLE = "Graphs - 3 vertices per triangle";
                    break;
                case sf::Keyboard::Num2:
                    current_figure = FigureType::Line;
                    vertex_buffer = sf::VertexBuffer(sf::PrimitiveType::Lines);
                    WindowController::TITLE = "Graphs - diagonal lines";
                    break;
                case sf::Keyboard::Num3:
                    current_figure = FigureType::Triangle;
                    vertex_buffer = sf::VertexBuffer(sf::PrimitiveType::Triangles);
                    WindowController::TITLE = "Graphs - filled triangles of fixed size";
                    break;
                case sf::Keyboard::Num4:
                    current_figure = FigureType::Rectangle;
                    vertex_buffer = sf::VertexBuffer(sf::PrimitiveType::Quads);
                    WindowController::TITLE = "Graphs - filled rectangles of fixed size";
                    break;
                case sf::Keyboard::Num5:
                    current_figure = FigureType::Circle;
                    vertex_buffer = sf::VertexBuffer(sf::PrimitiveType::Triangles);
                    WindowController::TITLE = "Graphs - filled circles of fixed size";
                    break;
                case sf::Keyboard::BackSpace:
                    if (!figures.empty())
                    {
                        figures.pop_back();
                        vertices.clear();
                        for (auto& figure : figures)
                        {
                            for (auto& vertex : figure.getVertices())
                            {
                                vertices.push_back(vertex);
                            }
                        }
                        vertex_buffer.create(vertices.size());
                        vertex_buffer.update(vertices.data());
                    }
                    break;
                case sf::Keyboard::Delete:
                    figures.clear();
                    vertices.clear();
                    vertex_buffer.create(vertices.size());
                    vertex_buffer.update(vertices.data());
                    break;
                case sf::Keyboard::Space:
                    //
                    break;
                default:
                    break;
            }
            figures.clear();
            vertices.clear();
            window.setTitle(WindowController::TITLE);
            break;
        default:
            break;
        }
    }
}


void WindowController::draw()
{
    window.draw(vertex_buffer);
}


void WindowController::addDrawable()
{
    // get the current position of the mouse
    sf::Vector2i mouse_position = sf::Mouse::getPosition(WindowController::window);
    // draw a triangle at the mouse position
    Figure figure(WindowController::current_figure, sf::Vector2f(mouse_position));
    figures.push_back(figure);
    for (auto& vertex : figure.getVertices())
    {
        vertices.push_back(vertex);
    }
    vertex_buffer.create(vertices.size());
    vertex_buffer.update(vertices.data());
}