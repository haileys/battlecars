#ifndef PLAYER_HH
#define PLAYER_HH

class Player;

#include <string>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "server/server.hh"

class Player
{
	static void ThreadFunc(void* ply);

public:
    uint32_t id;
    std::wstring name;
    float x, y, velocity, heading;
    
    sf::SocketTCP client;
    sf::IPAddress address;
    sf::Thread* thread;
    sf::Mutex thread_mutex;
    Server& server;
    
    Player(Server& _server, uint32_t _id, std::wstring _name);
    ~Player();
    
    void CompleteHandshake(std::wstring& motd);
    void SendPacket(sf::Packet& packet);
	void Run();
    
    sf::Packet InfoPacket();
    sf::Packet PositionPacket();
};

#endif
