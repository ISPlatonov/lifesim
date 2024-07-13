#include "Brain.hpp"
#include "Math.hpp"
#include "Event.hpp"
#include <future>


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
    std::vector<sf::Vector2f> shifts(players.size());
    std::vector<std::future<Event::Event>> futures;
    // handle players in thread pool
    for (size_t i = 0; i < players.size(); ++i)
    {
        std::future<Event::Event> future = std::async(std::launch::async, [&, i] {
            std::vector<std::shared_ptr<Food>> food_in_front(15);
            std::shared_ptr<Player> player_in_front;
            // make 15 rays in front of the player
            size_t rays_count = 15;
            Player& player = players[i];
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
            Event::Event event = player.make_turn(food_in_front, player_in_front);
            shifts[i] = event.getObjectPtr()->getPosition();
            return event;
        });
        futures.push_back(std::move(future));
    }
    // wait for all threads to finish
    for (auto& future : futures)
    {
        future.wait();
    }
    for (auto it = players.begin(); it != players.end();)
    {
        if (it->getHealth() <= 0)
        {
            foods.push_back(Food({it->getPosition().x, it->getPosition().y}));
            shifts.erase(shifts.begin() + (it - players.begin()));
            it = players.erase(it);
            continue;
            //players.push_back(Player({static_cast<float>(rand() % Constants::WIDTH), static_cast<float>(rand() % Constants::HEIGHT)}));
        }
        else
        {
            it->shift(shifts[it - players.begin()].x, shifts[it - players.begin()].y);
            for (auto& food : foods)
            {
                if (Math::distance(it->getPosition(), food.getPosition()) < Constants::Figures::FIGURE_SIZE * 2)
                {
                    // std::cout << "Player " << &it << " (" << it->getGenome().getGenes().size() << ") " << " eats food " << &food << " (" << it->getSatiety() << ")" << std::endl;
                    it->eat(food);
                    foods.erase(std::find(foods.begin(), foods.end(), food));
                    break;
                }
            }
            // check if the player is near the other player
            for (auto& other_player : players)
            {
                if (it->getSex() != other_player.getSex() && Math::distance(it->getPosition(), other_player.getPosition()) < Constants::Figures::FIGURE_SIZE * 2 && it->getSatiety() > 100 && other_player.getSatiety() > 100 && it->getReadyToReproduce() && other_player.getReadyToReproduce())
                {
                    auto child = it->reproduce(other_player);
                    // std::cout << "new player: " << child.getGenome().getGenes().size() << std::endl;
                    new_players.push_back(child);
                    shifts.push_back({0, 0});
                    break;
                }
            }
            ++it;
        }
    }
    // for (size_t i = foods.size(); i < FOODS_COUNT; ++i)
    // {
    //     foods.push_back(Food({static_cast<float>(rand() % (Constants::WIDTH / 2)), static_cast<float>(rand() % Constants::HEIGHT)}));
    //     break;
    // }
    for (size_t i = players.size(); i < PLAYERS_COUNT; ++i)
    {
        players.push_back(Player({static_cast<float>(rand() % (Constants::WIDTH / 2) + (Constants::WIDTH / 2)), static_cast<float>(rand() % Constants::HEIGHT)}));
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