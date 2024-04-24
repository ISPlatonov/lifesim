#include "Brain.hpp"
#include <cmath>


Brain::Brain()
{
    for (size_t i = 0; i < PLAYERS_COUNT; ++i)
    {
        players.push_back(Player({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
    }
    for (size_t i = 0; i < FOODS_COUNT; ++i)
    {
        foods.push_back(Food({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
    }
}


void Brain::make_turn(std::vector<Figure>& figures)
{
    for (auto& player : players)
    {
        std::vector<Food> food_positions, eaten_foods;
        for (auto& food : foods)
        {
            if (sqrt(pow(player.getPosition().x - food.getPosition().x, 2) + pow(player.getPosition().y - food.getPosition().y, 2)) <= player.VIEW_RADIUS)
            {
                food_positions.push_back(food);
            }
        }
        eaten_foods = player.make_turn(food_positions);
        for (auto& eaten_food : eaten_foods)
        {
            player.eat(eaten_food);
            foods.erase(std::find(foods.begin(), foods.end(), eaten_food));
            foods.push_back(Food({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
        }
    }
    for (auto it = players.begin(); it != players.end();)
    {
        if (it->getHealth() <= 0)
        {
            it = players.erase(it);
        }
        else
        {
            ++it;
        }
    }
    for (auto& player : players)
    {
        figures.push_back(Figure(FigureType::Triangle, player.getPosition(), player.getColor()));
    }
    for (auto& food : foods)
    {
        figures.push_back(Figure(FigureType::Circle, food.getPosition(), food.getColor()));
    }
}