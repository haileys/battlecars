#include "server/server.hh"
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstdarg>
#include <limits>

Server::Server(uint16_t _port)
    : client_id_autoinc(1), port(_port)
{
    if(!listener.Bind(port)) {
        Fatal("Could not bind to port %d", port);
    } else {
        Log("Bound to port %d", port);
    }
}

Server::~Server()
{
    listener.Unbind();
}

void Server::Run()
{
    Log("Running");
    while(true) {
        sf::Packet packet;
        sf::IPAddress ip;
        uint16_t _port;
        if(listener.Receive(packet, ip, _port) == sf::Socket::Done) {
            std::pair<sf::IPAddress, uint16_t> remote = std::make_pair(ip, _port);
            if(clients_by_remote_endpoint.find(remote) != clients_by_remote_endpoint.end()) {
                clients_by_remote_endpoint[remote]->HandlePacket(packet);
            } else if(pending_clients.find(remote) != pending_clients.end()) {
                HandlePendingClient(packet, remote);
            } else {
                HandleNewClient(packet, ip, _port);
            }
        }
    }
}

Client* Server::GetClient(uint32_t id)
{
    if(clients_by_id.find(id) != clients_by_id.end()) {
        return clients_by_id[id];
    } else {
        return NULL;
    }
}

void Server::Disconnect(uint32_t id)
{
    Client* client = clients_by_id[id];
    clients_by_remote_endpoint.erase(std::make_pair(client->address, client->port));
    Log("'%s' disconnected", client->name.c_str());
    delete client;
    clients_by_id.erase(id);
    sf::Packet packet;
    packet << PacketTypes::PACKET_PART << id;
    Broadcast(packet);
}

void Server::SendPacket(sf::IPAddress& address, uint16_t _port, sf::Packet& packet)
{
    listener.Send(packet, address, _port);
}

void Server::Broadcast(sf::Packet& packet)
{
    for(std::map<uint32_t, Client*>::iterator iter = clients_by_id.begin(); iter != clients_by_id.end(); ++iter) {
        iter->second->Send(packet);
    }
}

void Server::HandlePendingClient(sf::Packet& packet, std::pair<sf::IPAddress, uint16_t> ip_port)
{
    PendingClient p = pending_clients[ip_port];
    pending_clients.erase(ip_port);
    uint32_t type, a, b;
    if(!(packet >> type >> a >> b) || type != PacketTypes::PACKET_HANDSHAKE_NONCE) {
        return;
    }
    // verify that the other end is somewhat smart and not just a dumb udp sender
    if(!(a == (p.a + p.b) && b == (p.a ^ p.b))) {
        Warn("'%s' failed nonce. Expected (%d, %d), received (%d, %d)", p.name.c_str(), p.a + p.b, p.a ^ p.b, a, b);
        return;
    }
    // looks like a legit client...
    Client* client = new Client(*this, ip_port.first, ip_port.second, client_id_autoinc++, p.name);
    clients_by_remote_endpoint[ip_port] = client;
    clients_by_id[client->id] = client;
    // welcome the client
    sf::Packet welcome;
    welcome << PacketTypes::PACKET_HANDSHAKE_NONCE << client->id;
    for(int i = 0; i < 3; i++) {
        client->Send(welcome);
    }
    // broadcast join
    sf::Packet join;
    join << PacketTypes::PACKET_JOIN << client->id << client->name << client->x << client->y << client->velocity << client->heading;
    for(int i = 0; i < 3; i++) {
        // repeat join packet several times to account for packet loss
        Broadcast(join);
    }
    Log("'%s' joined", p.name.c_str());
}

void Server::HandleNewClient(sf::Packet& packet, sf::IPAddress& ip, uint16_t _port)
{
    // handshake properly
    uint32_t type;
    std::string name(1,0);
    if(!(packet >> type) || type != PacketTypes::PACKET_HANDSHAKE || !(packet >> name)) {
        // if it's just ping packet, pong back to the client
        if(type == PacketTypes::PACKET_PING) {
            sf::Packet response;
            response << PacketTypes::PACKET_PING;
            SendPacket(ip, _port, response);
        }
        return;
    }
    // create and register client
    Log("'%s' handshaking from %s:%d...", name.c_str(), ip.ToString().c_str(), _port);
    uint32_t a = sf::Randomizer::Random(0, std::numeric_limits<int32_t>::max());
    uint32_t b = sf::Randomizer::Random(0, std::numeric_limits<int32_t>::max());
    pending_clients[std::make_pair(ip, _port)] = PendingClient(a, b, name);
    sf::Packet nonce;
    nonce << PacketTypes::PACKET_HANDSHAKE << a << b;
    SendPacket(ip, _port, nonce);
}

void Server::Log(std::string msg, ...)
{
    printf("%09.2f LOG   ", clock.GetElapsedTime());
    va_list v;
    va_start(v, msg);
    vprintf(msg.c_str(), v);
    printf("\n");
}

void Server::Warn(std::string msg, ...)
{
    printf("%09.2f WARN  ", clock.GetElapsedTime());
    va_list v;
    va_start(v, msg);
    vprintf(msg.c_str(), v);
    printf("\n");
}

void Server::Fatal(std::string msg, ...)
{
    printf("%09.2f FATAL ", clock.GetElapsedTime());
    va_list v;
    va_start(v, msg);
    vprintf(msg.c_str(), v);
    printf("\n");
    exit(1);
}