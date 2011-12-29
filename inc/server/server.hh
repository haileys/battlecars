#ifndef SERVER_HH
#define SERVER_HH

class Server;

#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include "server/client.hh"
#include "shared/packet_types.hh"
#include <string>
#include <map>
#include <utility>
#include <stdint.h>

class Server
{
    uint32_t client_id_autoinc;
    uint16_t port;
    sf::SocketUDP listener;
    std::map<std::pair<sf::IPAddress, uint16_t>, PendingClient> pending_clients;
    std::map<std::pair<sf::IPAddress, uint16_t>, Client*> clients_by_remote_endpoint;
    std::map<uint32_t, Client*> clients_by_id;
    sf::Clock clock;
    
public:
    void Broadcast(sf::Packet& packet);
    
    Server(uint16_t _port);
    Client* GetClient(uint32_t id);
    void Run();
    void SendPacket(sf::IPAddress& address, uint16_t _port, sf::Packet& packet);
    void HandlePendingClient(sf::Packet& packet, std::pair<sf::IPAddress, uint16_t> ip_port);
    void HandleNewClient(sf::Packet& packet, sf::IPAddress& ip, uint16_t _port);
    void Log(std::string fmt, ...);
    void Warn(std::string fmt, ...);
    void Fatal(std::string fmt, ...);
    ~Server();
};

#endif
