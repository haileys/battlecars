#include "server/client.hh"
#include "shared/packet_types.hh"

PendingClient::PendingClient()
{ }
PendingClient::PendingClient(uint32_t _a, uint32_t _b, std::string& _name)
    : a(_a), b(_b), name(_name)
{ }

Client::Client(Server& _server, sf::IPAddress& _address, uint16_t _port, uint32_t _id, std::string& _name)
    : server(_server), address(_address), port(_port), id(_id), name(_name),
      x(0.0), y(0.0), velocity(0.0), heading(0.0)
{ }

Client::~Client()
{ }

void Client::Send(sf::Packet& packet)
{
    server.SendPacket(address, port, packet);
}

sf::Packet Client::InfoPacket()
{
    sf::Packet packet;
    packet << PacketTypes::PACKET_PLAYER_INFO << id << name << x << y << velocity << heading;
    return packet;
}

sf::Packet Client::PositionPacket()
{
    sf::Packet packet;
    packet << PacketTypes::PACKET_PLAYER_POSITION << id << x << y << velocity << heading;
    return packet;
}

void Client::HandlePacket(sf::Packet& packet)
{
//    fprintf(stderr, "                %x\n", *(uint32_t*)packet.GetData());
    
    uint32_t type = 0;
    if(!(packet >> type)) return;
    switch(type) {
        case PacketTypes::PACKET_PLAYER_INFO: {
            uint32_t req_id;
            if(!(packet >> req_id)) break;
            Client* requested = server.GetClient(req_id);
            if(requested) {
                sf::Packet p = requested->InfoPacket();
                Send(p);
            }
        } break;
        case PacketTypes::PACKET_PLAYER_POSITION: {
            // @TODO implement sanity checks for max velocity vs. position delta
            // @TODO rate limit broadcasts to other clients
            float new_x, new_y, new_velocity, new_heading;
            if(!(packet >> new_x >> new_y >> new_velocity >> new_heading)) return;
            x = new_x;
            y = new_y;
            velocity = new_velocity;
            heading = new_heading;
            sf::Packet p = PositionPacket();
            server.Broadcast(p);
        } break;
        case PacketTypes::PACKET_PART: {
            // this is the part where we delete ourselves. uh oh!
            server.Disconnect(id);
            // now get the fuck out of here
            return;
        };
        default: {
            server.Warn("Unknown packet type %d from %s", type, name.c_str());
        } break;
    }
}