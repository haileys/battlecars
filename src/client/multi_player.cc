#include "client/multi_player.hh"
#include "shared/packet_types.hh"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <string>
#include <Gwen/Skin.h>
#include <Gwen/Skins/Simple.h>
#include <Gwen/Skins/TexturedBase.h>
#include <Gwen/UnitTest/UnitTest.h>

MultiPlayer::MultiPlayer(Game& _game, sf::IPAddress& _server_ip, uint16_t _server_port)
    : Scene(_game), server_ip(_server_ip), server_port(_server_port), me(NULL)
{
    while(true) {
        uint16_t port = sf::Randomizer::Random(20000, 65535);
        if(server.Bind(port)) break;
    }
    server.SetBlocking(false);
    printf("connecting to %s:%d\n", server_ip.ToString().c_str(), server_port);
    
    sf::Packet handshake;
    handshake << PacketTypes::PACKET_HANDSHAKE << std::string("Dumb Schmuck");
    SendPacket(handshake);
    
    background_image.LoadFromFile("assets/bg2.png");
    background_image.SetSmooth(false);
    background = sf::Sprite(background_image);
    background.Move(-100, -99);
    
    /*
    car = sf::Sprite(game.assets.Image("assets/car.png"));
    car.SetCenter(32, 32);
    */
    
    coords = sf::String("", game.assets.Font("assets/UbuntuMono-R.ttf"), 24);
    coords.SetColor(sf::Color(0, 0, 0, 255));
}

MultiPlayer::~MultiPlayer()
{
    sf::Packet leave;
    leave << PacketTypes::PACKET_PART;
    for(int i = 0; i < 3; i++) {
        server.Send(leave, server_ip, server_port);
    }
    for(std::map<uint32_t, Player*>::iterator iter = players.begin(); iter != players.end(); ++iter) {
        delete iter->second;
    }
}

void MultiPlayer::SendPacket(sf::Packet& packet)
{
    server.Send(packet, server_ip, server_port);
}

void MultiPlayer::HandlePacket(sf::Packet& packet)
{
    uint32_t type;
    if(!(packet >> type)) return;
    switch(type) {
        case PacketTypes::PACKET_HANDSHAKE: {
            uint32_t a, b;
            if(!(packet >> a >> b)) break;
            sf::Packet response;
            response << PacketTypes::PACKET_HANDSHAKE_NONCE;
            response << (a + b) << (a ^ b);
            SendPacket(response);
        } break;
        case PacketTypes::PACKET_HANDSHAKE_NONCE: {
            uint32_t id;
            if(!(packet >> id)) break;
            my_id = id;
        } break;
        case PacketTypes::PACKET_JOIN: {
            uint32_t id;
            std::string name(1, 0);
            float x, y, velocity, heading;
            if(!(packet >> id >> name >> x >> y >> velocity >> heading)) break;
            players[id] = new Player(game, id, name, x, y, velocity, heading);
            if(my_id == id) {
                me = players[id];
            }
            players[id]->car.SetCenter(32, 32);
        } break;
        case PacketTypes::PACKET_PLAYER_POSITION: {
            uint32_t id;
            float x, y, velocity, heading;
            if(!(packet >> id >> x >> y >> velocity >> heading)) break;
            if(id == my_id) break;
            if(players.find(id) == players.end()) {
                // this player existed before joining, so we'll ask for its info
                // but disregard this packet
                sf::Packet request;
                request << PacketTypes::PACKET_PLAYER_INFO << id;
                SendPacket(request);
            } else {
                Player& ply = *players[id];
                ply.x = x;
                ply.y = y;
                ply.velocity = velocity;
                ply.heading = heading;
            }
        } break;
        case PacketTypes::PACKET_PLAYER_INFO: {
            uint32_t id;
            std::string name(1, 0);
            float x, y, velocity, heading;
            if(!(packet >> id >> name >> x >> y >> velocity >> heading)) break;
            if(players.find(id) == players.end()) {
                players[id] = new Player(game, id, name, x, y, velocity, heading);
                players[id]->car.SetCenter(32, 32);
            } else {
                Player& ply = *players[id];
                ply.x = x;
                ply.y = y;
                ply.velocity = velocity;
                ply.heading = heading;
            }
        } break;
        case PacketTypes::PACKET_PART: {
            uint32_t id;
            if(!(packet >> id)) break;
            if(players.find(id) == players.end()) break;
            delete players[id];
            players.erase(id);
        } break;
        default: {
            printf("unknown packet type %d\n", type);
        } break;
    }
}

void MultiPlayer::Tick()
{    
    // handle any incoming packets from the server
    sf::Packet recv;
    sf::IPAddress addr;
    uint16_t port;
    while(server.Receive(recv, addr, port) == sf::Socket::Done) {
        if(/*addr == server_ip && @TODO */ port == server_port) {
            HandlePacket(recv);
        }
    }
    
    if(!me) return;
    
    // change our own velocity and crap based on input from the player
    if(game.input.IsKeyDown(sf::Key::Up)) {
        target_velocity = 300;
        if(me->velocity < 0) me->velocity = 0;
    } else if(game.input.IsKeyDown(sf::Key::Down)) {
        target_velocity = -300;
        if(me->velocity > 0) me->velocity = 0;
    } else {
        target_velocity = 0;
    }
    
    // heading
    if(game.input.IsKeyDown(sf::Key::Right)) {
        me->heading += 1/(float)Game::TICKS_PER_SECOND * 0.015 * me->velocity;
    } else if(game.input.IsKeyDown(sf::Key::Left)) {
        me->heading -= 1/(float)Game::TICKS_PER_SECOND * 0.015 * me->velocity;
    }
    
    if(me->velocity != target_velocity) {
        if(me->velocity > target_velocity) {
            me->velocity -= 3;
        } else {
            me->velocity += 3;
        }
    }
    
    // send server new velocity/heading
    if(++position_update_tick == 20) {
        position_update_tick = 0;
        sf::Packet pos;
        pos << PacketTypes::PACKET_PLAYER_POSITION << me->x << me->y << me->velocity << me->heading;
        SendPacket(pos);
    }
    
    // update all players positions based on their velocities and heading
    for(std::map<uint32_t, Player*>::iterator iter = players.begin(); iter != players.end(); ++iter) {
        Player& ply = *iter->second;
        float factor = ply.velocity / (float)Game::TICKS_PER_SECOND;
        ply.x += sin(ply.heading) * factor;
        ply.y += cos(ply.heading) * factor;
    }
    
    // center the view on our own car
    game.view.SetCenter(sf::Vector2f(game.window.GetWidth() / 2.0 + me->x, game.window.GetHeight() / 2.0 - me->y));
    game.window.SetView(game.view);
}

void MultiPlayer::DrawHud()
{
    /*
    char coords_buff[64];
    sprintf(coords_buff, "(%d, %d), %d\n%.2f km/h", (int)x, (int)y, (int)(-heading * 180.0 / M_PI) % 360, (velocity / 15.0) * 3.6);
    coords.SetText(sf::Unicode::Text(coords_buff));
    coords.SetPosition(16, 8);
    game.window.Draw(coords);
    */
}

void MultiPlayer::Draw()
{
    if(!me) return;
    
    int cx = (int)(game.window.GetWidth() / 2.0 + me->x);
    int cy = (int)(game.window.GetHeight() / 2.0 - me->y);
    cx /= background.GetSize().x;
    cx *= background.GetSize().x;
    cy /= background.GetSize().y;
    cy *= background.GetSize().y;
    int y_factor = (game.window.GetHeight() / background.GetSize().y) + 1;
    int x_factor = (game.window.GetWidth() / background.GetSize().x) + 1;
    
    for(int j = -y_factor; j <= y_factor; j++) {
        for(int i = -x_factor; i <= x_factor; i++) {
            background.SetPosition(cx + i * background.GetSize().x, cy + j * background.GetSize().y);
            game.window.Draw(background);
        }
    }
    
    int mid_x = game.window.GetWidth() / 2.0;
    int mid_y = game.window.GetHeight() / 2.0;
    for(std::map<uint32_t, Player*>::iterator iter = players.begin(); iter != players.end(); ++iter) {
        Player& ply = *iter->second;
        ply.car.SetPosition(mid_x + ply.x, mid_y - ply.y);
        ply.label.SetPosition(mid_x + ply.x - (ply.label_width / 2), mid_y - ply.y + 32);
        ply.car.SetRotation(-ply.heading * 180.0 / M_PI);
        game.window.Draw(ply.car);
        game.window.Draw(ply.label);
    }
}

bool MultiPlayer::DispatchEvent(sf::Event& ev)
{
    return false;
}
