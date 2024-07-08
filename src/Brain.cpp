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
        std::vector<std::shared_ptr<Food>> food_in_front(15);
        std::shared_ptr<Player> player_in_front;
        // make 5 rays in front of the player
        size_t rays_count = 15;
        for (float angle = -Constants::Figures::PI / 4 + player.getAngle(); angle <= Constants::Figures::PI / 4 + player.getAngle(); angle += Constants::Figures::PI / 28)
        {
            --rays_count;
            for (auto& food : foods)
            {
                if (Math::in_front(player.getPosition(), angle, food.getPosition()))
                {
                    food_in_front[rays_count] = std::make_shared<Food>(food);
                }
            }
        }
        // for (auto& other_player : players)
		// {
        //     if (player == other_player) {
        //         continue;
        //     } else if (Math::in_front(player.getPosition(), player.getAngle(), other_player.getPosition())) {
        //         if (!player_in_front || Math::distance(player.getPosition(), other_player.getPosition()) < Math::distance(player.getPosition(), player_in_front->getPosition())) {
        //             player_in_front = std::make_shared<Player>(other_player);
        //         }
        //     }
		// }
        Event::Event event = player.make_turn(food_in_front, player_in_front);
        switch (event.getType())
        {
        case Event::Type::None:
            {
                // check if the player is near the food
                for (auto& food : foods)
                {
                    if (Math::distance(player.getPosition(), food.getPosition()) < Constants::Figures::FIGURE_SIZE * 2)
                    {
                        std::cout << "Player " << &player << " (" << player.getGenome().getGenes().size() << ") " << " eats food " << &food << " (" << player.getSatiety() << ")" << std::endl;
                        player.eat(food);
                        foods.erase(std::find(foods.begin(), foods.end(), food));
                        break;
                    }
                }
                // check if the player is near the other player
                for (auto& other_player : players)
                {
                    if (player.getSex() != other_player.getSex() && Math::distance(player.getPosition(), other_player.getPosition()) < Constants::Figures::FIGURE_SIZE * 2 && player.getSatiety() > 100 && other_player.getSatiety() > 100)
                    {
                        auto child = player.reproduce(other_player);
                        new_players.push_back(child);
                        break;
                    }
                }
            }
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
            //foods.push_back(Food({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
            it = players.erase(it);
            //players.push_back(Player({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
        }
        else
        {
            ++it;
        }
    }
    for (size_t i = foods.size(); i < FOODS_COUNT; ++i)
    {
        foods.push_back(Food({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
        break;
    }
    for (size_t i = players.size(); i < PLAYERS_COUNT; ++i)
    {
        players.push_back(Player({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
        break;
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