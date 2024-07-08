#include "Player.hpp"
#include "Math.hpp"
#include "Constants.hpp"


Player::Player(sf::Vector2f position) : Object(position, ObjectType::Player, sf::Color(rand() % 256, rand() % 256, rand() % 256)), genome(15, 2)
{
    speed = rand() % 10 + 1;
    view_radius = rand() % 1000 + 500;
    sex = rand() % 2 == 0 ? PlayerSex::Male : PlayerSex::Female;
}


Player::Player(const Player& first_parent, const Player& second_parent) : Object(first_parent.getPosition(), ObjectType::Player, sf::Color(first_parent.getColor().r / 2 + second_parent.getColor().r / 2, first_parent.getColor().g / 2 + second_parent.getColor().g / 2, first_parent.getColor().b / 2 + second_parent.getColor().b / 2)), genome(15, 2)
{
	speed = (first_parent.getSpeed() / 2.f + second_parent.getSpeed() / 2.f) + static_cast<float>(rand() % 3 - 1);
	view_radius = (first_parent.getViewRadius() / 2.f + second_parent.getViewRadius() / 2.f) + static_cast<float>(rand() % 3 - 1);
    sex = rand() % 2 == 0 ? PlayerSex::Male : PlayerSex::Female;
    health = (first_parent.getHealth() / 2 + second_parent.getHealth() / 2);
    satiety = (first_parent.getSatiety() / 2 + second_parent.getSatiety() / 2);
    genome = Genome(first_parent.getGenome(), second_parent.getGenome());
}


Event::Event Player::make_turn(std::vector<std::shared_ptr<Food>> food_in_front, std::shared_ptr<Player> player_in_front)
{
    satiety <= 0 ? health -= .1f : satiety -= .1f;
    Event::Event event(Event::Type::Move, std::nullptr_t());
    // @todo: Implement the logic of the player's behavior
    std::vector<float> input(food_in_front.size());
    for (size_t i = 0; i < food_in_front.size(); ++i)
    {
        input[i] = food_in_front[i] ? 1.f : 0.f;
        // std::cout << input[i] << ' ';
    }
    // std::cout << std::endl;
    auto action = genome.getOutput(input);
    //shift(action[0] * 2 * Constants::Figures::PI, action[1]);
    sf::Vector2f shift(action[0] * 2 * Constants::Figures::PI, action[1]);
    event = Event::Event(Event::Type::Move, std::make_shared<Object>(shift, ObjectType::None, sf::Color()));
    // check for food to eat
    bool eated = false;
    // for (auto& food : food_in_front)
    // {
    //     if (food && Math::distance(position, food->getPosition()) < Constants::Figures::FIGURE_SIZE * 2)
    //     {
    //         std::cout << "Player " << this << " eats food " << food.get() << std::endl;
    //         eat(*food);
    //         event = Event::Event(Event::Type::Eat, food);
    //         eated = true;
    //         break;
    //     }
    // }
    if (getSatiety() < 0) {
        genome.mutate();
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


Player Player::reproduce(Player& other)
{
    auto child = Player(*this, other);
    satiety -= 100.f;
    other.satiety -= 100.f;
    return child;
}



void Player::shift(float angle, float speed_share)
{
    std::abs(speed_share) > 1 ? speed_share /= std::abs(speed_share) : speed_share;
    this->angle += angle;
    this->angle = std::fmod(this->angle, 2.f * Constants::Figures::PI);
    position.x += speed_share * speed * cos(this->angle);
    position.y += speed_share * speed * sin(this->angle);
    satiety -= speed_share * speed * speed_share * speed * .001f;
}