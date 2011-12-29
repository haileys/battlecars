#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>
#include <stdint.h>
#include <SFML/Network.hpp>

class Player
{
public:
    uint32_t id;
    std::string name;
    float x, y, velocity, heading;
    
    Player(uint32_t _id, std::string& _name, float _x = 0.0, float _y = 0.0, float _velocity = 0.0, float _heading = 0.0);
    
    void HandleInfoRemainder(sf::Packet& packet);
    void HandlePositionRemainder(sf::Packet& packet);
};

#endif