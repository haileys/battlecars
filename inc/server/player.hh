#ifndef PLAYER_HH
#define PLAYER_HH

class Player;

#include <string>
#include <SFML/Network.hpp>
#include "server/server.hh"

class Player
{
public:
    uint32_t id;
    std::wstring name;
    float x, y, velocity, heading;
    
    sf::SocketTCP client;
    sf::IPAddress address;
    Server& server;
    
    Player(Server& _server, uint32_t _id, std::wstring _name);
    void CompleteHandshake(std::wstring& motd);
    void SendPacket(sf::Packet& packet);
    
    sf::Packet InfoPacket();
    sf::Packet PositionPacket();
};

#endif