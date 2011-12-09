#include "server/server.hh"
#include <iostream>

Server::Server(uint16_t _port)
    : port(_port), motd(L"Welcome to Battlecars")
{
    listener.Listen(port);
    listener.SetBlocking(false);
    selector.Add(listener);
}

void Server::AcceptClient()
{
    sf::SocketTCP client;
    sf::IPAddress ip;
    if(listener.Accept(client, &ip) != sf::Socket::NotReady) {
        accepted[client] = ip;
        selector.Add(client);
        std::wcout << L"Accepted client from ";
        std::cout << ip.ToString();
        std::wcout << std::endl;
    }
}

void Server::ClientReady(sf::SocketTCP& socket)
{
    if(accepted.find(socket) != accepted.end()) {
        // just connected client has sent a packet
        sf::SocketTCP sock = socket;
        accepted.erase(socket);
        sf::Packet packet;
        if(socket.Receive(packet) == sf::Socket::Done && packet) {
            uint32_t packet_id;
            uint32_t player_id;
            std::wstring player_name;
            packet >> packet_id >> player_id >> player_name;
            if(packet && packet_id == PACKET_HANDSHAKE) {
                if(players.find(player_id) != players.end()) {
                    sf::Packet kick;
                    kick << (uint32_t)PACKET_KICK << L"A user with your ID is already playing on this server";
                    sock.Send(kick);
                } else {
                    // successful connect
                    Player player(*this, player_id, player_name);
                    std::wcout << L"Player '" << player_name << L"' (" << player_id << L") joined" << std::endl;
                }
            }
        }
        selector.Remove(sock);
        sock.Close();
    }
}

void Server::Broadcast(sf::Packet packet)
{
    for(std::map<uint32_t,Player>::iterator iter = players.begin(); iter != players.end(); ++iter) {
        iter->second.SendPacket(packet);
    }
}

void Server::DisconnectClient(sf::SocketTCP& socket)
{
    if(accepted.find(socket) != accepted.end()) {
        accepted.erase(socket);
        return;
    }
    if(sockets_ids.find(socket) != sockets_ids.end()) {
        uint32_t player_id = sockets_ids[socket];
        sockets_ids.erase(socket);
        players.erase(player_id);
        socket.Close();
        sf::Packet notification;
        notification << (uint32_t)PACKET_PART << player_id;
        Broadcast(notification);
        return;
    }
}

void Server::Run()
{
    running = true;
    while(running)
    {
        size_t ready = selector.Wait();
        for(size_t i = 0; i < ready; i++) {
            sf::SocketTCP sock = selector.GetSocketReady(i);
            if(sock == listener) {
                AcceptClient();
            } else {
                ClientReady(sock);
            }
        }
    }
}

Server::~Server()
{
    selector.Clear();
    listener.Close();
}