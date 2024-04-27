#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Food.hpp"
#include "Event.hpp"
#include <vector>


enum class PlayerSex
{
    Male,
    Female
};


class Player : public Object
{
public:
    Player(sf::Vector2f position);
    Player(const Player& first_parent, const Player& second_parent);
    ~Player() = default;

    Event::Event make_turn(std::vector<Food> foods_around, std::vector<Player> players_around);
    inline float getViewRadius() const { return view_radius; }
    inline int getHealth() const { return health; }
    inline int getSatiety() const { return satiety; }
    inline float getSpeed() const { return speed; }
    inline PlayerSex getSex() const { return sex; }
    inline bool operator==(const Player& other) const { return position == other.position && health == other.health && color == other.color && view_radius == other.view_radius && sex == other.sex; }

protected:
    void eat(const Food& food);
    std::vector<Food>::iterator search_for_nearest(std::vector<Food>& foods_around);
    std::vector<Player>::iterator search_for_nearest(std::vector<Player>& players_around, bool opposite_sex = false);

private:
    void shift(const sf::Vector2f& shift_vector);

    float health = 20.f;
    float satiety = 20.f;
    float view_radius;
    //size_t damage = 10;
    float speed;
    PlayerSex sex;
};