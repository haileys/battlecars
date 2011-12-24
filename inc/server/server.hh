#ifndef SERVER_HH
#define SERVER_HH

class Server;

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "server/player.hh"
#include <string>
#include <map>
#include <stdint.h>

class Server
{
    bool running;
    uint16_t port;
    std::wstring motd;
    sf::SocketTCP listener;
    sf::Mutex mutex;
    std::map<uint32_t, Player> players;
    std::map<sf::SocketTCP, uint32_t> sockets_ids;
    std::map<sf::SocketTCP, sf::IPAddress> accepted;
    
    void Broadcast(sf::Packet packet);
    void DisconnectClient(sf::SocketTCP& socket);
    void AcceptClient();
    void ClientReady(sf::SocketTCP& socket);
    
public:
    enum PacketType
    {
        PACKET_HANDSHAKE        = 1,
        PACKET_PLAYER_INFO      = 2,
        PACKET_PLAYER_POSITION  = 3,
        PACKET_JOIN             = 4,
        PACKET_PART             = 5,
        PACKET_KICK             = 6
    };
    
    Server(uint16_t _port);
    void Run();
    ~Server();
};

#endif
