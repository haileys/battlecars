#ifndef PLAYER_HH
#define PLAYER_HH

#include <wstring>

class Player
{    
    uint32_t id;
    std::wstring name;
    float x, y, velocity, heading;
};

#endif