#pragma once

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include "Food.hpp"
#include "Event.hpp"
#include "Genome.hpp"
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

    Event::Event make_turn(std::vector<std::shared_ptr<Food>> food_in_front, std::shared_ptr<Player> player_in_front);
    inline float getViewRadius() const { return view_radius; }
    inline int getHealth() const { return health; }
    inline int getSatiety() const { return satiety; }
    inline float getSpeed() const { return speed; }
    inline PlayerSex getSex() const { return sex; }
    inline float getAngle() const { return angle; }
    inline Genome getGenome() const { return genome; }
    inline bool operator==(const Player& other) const { return position == other.position && health == other.health && color == other.color && view_radius == other.view_radius && sex == other.sex; }
    void eat(const Food& food);
    Player reproduce(Player& other);

protected:
    std::vector<Food>::iterator search_for_nearest(std::vector<Food>& foods_around);
    std::vector<Player>::iterator search_for_nearest(std::vector<Player>& players_around, bool opposite_sex = false);

private:
    void shift(float angle, float speed_share);

    Genome genome;
    float health = 20.f;
    float satiety = 20.f;
    float view_radius;
    //size_t damage = 10;
    float speed;
    PlayerSex sex;
    float angle = 0.f;
};