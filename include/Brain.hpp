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
#include <boost/asio.hpp>
#include <boost/thread.hpp>


class Brain
{
public:
    Brain();

    void make_turn(std::vector<Figure>& figures);
    inline boost::asio::io_service& get_io_service() { return io_service; }

private:
    std::vector<Player> players;
    std::vector<Food> foods;

    static inline const size_t PLAYERS_COUNT = 20;
    static inline const size_t FOODS_COUNT = 100;
    // thread pool
    boost::asio::io_service io_service;
    boost::thread_group threadpool;
};