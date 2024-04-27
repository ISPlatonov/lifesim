#include "Player.hpp"
#include "Math.hpp"


Player::Player(sf::Vector2f position) : Object(position, ObjectType::Player, sf::Color(rand() % 256, rand() % 256, rand() % 256))
{
    speed = rand() % 10 + 1;
    view_radius = rand() % 1000 + 500;
    sex = rand() % 2 == 0 ? PlayerSex::Male : PlayerSex::Female;
}


Player::Player(const Player& first_parent, const Player& second_parent) : Object(first_parent.getPosition(), ObjectType::Player, sf::Color(first_parent.getColor().r / 2 + second_parent.getColor().r / 2, first_parent.getColor().g / 2 + second_parent.getColor().g / 2, first_parent.getColor().b / 2 + second_parent.getColor().b / 2))
{
	speed = (first_parent.getSpeed() / 2.f + second_parent.getSpeed() / 2.f) + static_cast<float>(rand() % 3 - 1);
	view_radius = (first_parent.getViewRadius() / 2.f + second_parent.getViewRadius() / 2.f) + static_cast<float>(rand() % 3 - 1);
    sex = rand() % 2 == 0 ? PlayerSex::Male : PlayerSex::Female;
    health = (first_parent.getHealth() / 2 + second_parent.getHealth() / 2);
    satiety = (first_parent.getSatiety() / 2 + second_parent.getSatiety() / 2);
}


Event::Event Player::make_turn(std::vector<Food> foods_around, std::vector<Player> players_around)
{
    satiety <= 0 ? health -= 1.f : satiety -= .1f;
    Event::Event event(Event::Type::None, std::nullptr_t());
    // let's move to the nearest food if we are hungry
    if (satiety < 250)
    {
        if (foods_around.empty())
        {
            // do nothing?
            return event;
        }
        auto nearest_food_iter = search_for_nearest(foods_around);
        if (nearest_food_iter != foods_around.end())
        {
            auto shift_vector = nearest_food_iter->getPosition() - position;
            shift(shift_vector);
            if (Math::length(shift_vector) < speed)
            {
                eat(*nearest_food_iter);
                event = Event::Event(Event::Type::Eat, std::make_shared<Food>(*nearest_food_iter));
            }
        }
    }
    else
    {
        if (players_around.empty())
        {
            // do nothing?
            return event;
        }
        // let's move to person with of the opposite sex
        auto nearest_player_iter = search_for_nearest(players_around, true);
        if (nearest_player_iter != players_around.end() && nearest_player_iter->getSex() != sex)
        {
            auto shift_vector = nearest_player_iter->getPosition() - position;
            shift(shift_vector);
            if (Math::length(shift_vector) < speed)
            {
                health /= 2;
                nearest_player_iter->health /= 2;
                event = Event::Event(Event::Type::Sex, std::make_shared<Player>(*nearest_player_iter));
                satiety = 0;
            }
        }
    }
    return event;
}


std::vector<Food>::iterator Player::search_for_nearest(std::vector<Food>& foods)
{
    auto iterator = foods.begin();
    for (auto it = foods.begin(); it != foods.end(); ++it)
    {
        if (Math::distance(position, it->getPosition()) < Math::distance(position, iterator->getPosition()))
        {
            iterator = it;
        }
    }
    return iterator;
}


std::vector<Player>::iterator Player::search_for_nearest(std::vector<Player>& players, bool opposite_sex)
{
    auto iterator = players.begin();
    for (auto it = players.begin(); it != players.end(); ++it)
    {
        if (Math::distance(position, it->getPosition()) < Math::distance(position, iterator->getPosition()))
        {
            iterator = it;
        }
    }
    return iterator;
}


void Player::eat(const Food& food)
{
    satiety += food.getSatietyBonus();
    satiety = std::min(satiety, 1000.f);
    health += food.getHealthBonus();
    health = std::min(health, 1000.f);
}


void Player::shift(const sf::Vector2f& shift_vector)
{
    float length = Math::length(shift_vector);
    length > speed ? position += shift_vector / length * speed : position += shift_vector;
}