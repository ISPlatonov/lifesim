#include "Brain.hpp"
#include "Math.hpp"
#include "Event.hpp"


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
    std::vector<Player> new_players;
    for (auto& player : players)
    {
        std::vector<Food> food_around;
        std::vector<Player> players_around;
        for (auto& food : foods)
        {
            if (Math::distance(player.getPosition(), food.getPosition()) <= player.getViewRadius())
            {
                food_around.push_back(food);
            }
        }
        for (auto& other_player : players)
		{
			if (&player != &other_player && Math::distance(player.getPosition(), other_player.getPosition()) <= player.getViewRadius())
			{
				players_around.push_back(other_player);
			}
		}
        Event::Event event = player.make_turn(food_around, players_around);
        switch (event.getType())
        {
        case Event::Type::None:
            break;
        case Event::Type::Eat:
            {
                auto object_ptr = event.getObjectPtr();
                auto weak_ptr = object_ptr.get();
                Food* food = dynamic_cast<Food*>(weak_ptr);
                foods.erase(std::find(foods.begin(), foods.end(), *food));
            }
            break;
        case Event::Type::Sex:
        {
			auto object_ptr = event.getObjectPtr();
			auto weak_ptr = object_ptr.get();
			Player* other_player = dynamic_cast<Player*>(weak_ptr);
			new_players.push_back(Player(player, *other_player));
			break;
        }
        default:
            break;
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

    for (size_t i = 0; i < 1; ++i)
	{
		foods.push_back(Food({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
	}

    players.insert(players.end(), new_players.begin(), new_players.end());
    for (auto& player : players)
    {
        figures.push_back(Figure(player.getSex() == PlayerSex::Male ? FigureType::Male : FigureType::Female, player.getPosition(), player.getColor()));
    }
    for (auto& food : foods)
    {
        figures.push_back(Figure(FigureType::Circle, food.getPosition(), food.getColor()));
    }
}