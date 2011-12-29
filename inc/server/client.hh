#ifndef CLIENT_HH
#define CLIENT_HH

class Client;
class PendingClient;

#include <string>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "server/server.hh"

struct PendingClient {
    uint32_t a;
    uint32_t b;
    std::string name;
    PendingClient();
    PendingClient(uint32_t _a, uint32_t _b, std::string& _name);
};

class Client
{    
    Server& server;
    
public:
    sf::IPAddress address;
    uint16_t port;
    
    uint32_t id;
    std::string name;
    float x, y, velocity, heading;
    
    Client(Server& _server, sf::IPAddress& _address, uint16_t _port, uint32_t _id, std::string& _name);
    ~Client();
    
    void Send(sf::Packet& packet);
    
    sf::Packet InfoPacket();
    sf::Packet PositionPacket();
    
    void HandlePacket(sf::Packet& packet);
};

#endif
