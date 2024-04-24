#include "Player.hpp"


Player::Player(sf::Vector2f position) : position(position) 
{
    SPEED = rand() % 10 + 1;
    VIEW_RADIUS = rand() % 1000 + 500;
}


std::vector<Food> Player::make_turn(std::vector<Food> foods_around)
{
    health -= 1;
    std::vector<Food> eaten_foods;
    // let's move to the nearest food
    if (!foods_around.empty())
    {
        Food nearest_food = foods_around[0];
        for (auto& food : foods_around)
        {
            if (sqrt(pow(position.x - food.getPosition().x, 2) + pow(position.y - food.getPosition().y, 2)) <
                sqrt(pow(position.x - nearest_food.getPosition().x, 2) + pow(position.y - nearest_food.getPosition().y, 2)))
            {
                nearest_food = food;
            }
        }
        sf::Vector2f direction = nearest_food.getPosition() - position;
        shift(direction);
        if (position == nearest_food.getPosition())
        {
            // eat the food
            eaten_foods.push_back(nearest_food);
            foods_around.erase(std::find(foods_around.begin(), foods_around.end(), nearest_food));
        }
    }
    return eaten_foods;
}


void Player::eat(Food& food)
{
    health += food.getHealthBonus();
}


void Player::shift(const sf::Vector2f& shift_vector)
{
    float length = sqrt(pow(shift_vector.x, 2) + pow(shift_vector.y, 2));
    if (length > SPEED)
    {
        position += shift_vector / length * SPEED;
    }
    else
    {
        position += shift_vector;
    }
}