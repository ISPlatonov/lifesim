#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Figures.hpp"
#include "Constants.hpp"
#include "Player.hpp"
#include "Food.hpp"
#include "Object.hpp"
#include <vector>
#include <thread>


class Brain
{
public:
    Brain();

    void make_turn(std::vector<Figure>& figures);

private:
    std::vector<Player> players;
    std::vector<Food> foods;

    static inline const size_t PLAYERS_COUNT = 20;
    static inline const size_t FOODS_COUNT = 100;
};