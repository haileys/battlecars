#include "server/player.hh"

Player::Player(Server& _server, uint32_t _id, std::wstring _name)
    : id(_id), name(_name), x(0), y(0), velocity(0), heading(0), server(_server), thread(NULL)
{ }

Player::~Player()
{
	sf::Lock lock(thread_mutex);
	if(thread) {
		thread.Terminate();
		delete thread;
	}
}

void Player::ThreadFunc(void* ply)
{
	Player* player = (Player*)ply;
}

sf::Packet Player::InfoPacket()
{
    sf::Packet packet;
    packet << (uint32_t)Server::PACKET_PLAYER_INFO << id << name << x << y << velocity << heading;
    return packet;
}

sf::Packet Player::PositionPacket()
{
    sf::Packet packet;
    packet << (uint32_t)Server::PACKET_PLAYER_POSITION << id << x << y << velocity << heading;
    return packet;
}

void Player::CompleteHandshake(std::wstring& motd)
{
    sf::Packet handshake;
    handshake << (uint32_t)Server::PACKET_HANDSHAKE << motd;
    SendPacket(handshake);
    sf::Packet info = InfoPacket();
    SendPacket(info);
}

void Player::SendPacket(sf::Packet& packet)
{
    client.Send(packet);
}
