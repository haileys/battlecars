#ifndef MULTI_PLAYER_HH
#define MULTI_PLAYER_HH

#include "client/scene.hh"
#include "client/player.hh"
#include <SFML/Network.hpp>
#include <stdint.h>
#include <map>

class MultiPlayer : public Scene
{
    sf::IPAddress server_ip;
    uint16_t server_port;
    sf::SocketUDP server;
    
    sf::Image background_image;
    sf::Sprite background;
    sf::Sprite car;
    
    sf::String coords;
    
    std::map<uint32_t, Player*> players;
    int position_update_tick;
    uint32_t my_id;
    Player* me;
    float target_velocity;
    
public:
    void SendPacket(sf::Packet& packet);
    
    MultiPlayer(Game& _game, sf::IPAddress& _address, uint16_t _port);
    ~MultiPlayer();
    virtual void Draw();
    virtual void DrawHud();
    void HandlePacket(sf::Packet& packet);
    virtual void Tick();
    virtual bool DispatchEvent(sf::Event& ev);
};

#endif