#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <stdint.h>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "client/game.hh"

class Player
{
public:    
    Game& game;
    uint32_t id;
    std::string name;
    float x, y, velocity, heading;
    sf::Sprite car;
    sf::String label;
    int label_width;
    
    Player(Game& _game, uint32_t _id, std::string& _name, float _x = 0.0, float _y = 0.0, float _velocity = 0.0, float _heading = 0.0);
    
    void HandleInfoRemainder(sf::Packet& packet);
    void HandlePositionRemainder(sf::Packet& packet);
};

#endif