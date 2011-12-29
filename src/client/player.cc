#include "client/player.hh"

Player::Player(uint32_t _id, std::string& _name, float _x, float _y, float _velocity, float _heading)
    : id(_id), name(_name), x(_x), y(_y), velocity(_velocity), heading(_heading)
{
    
}