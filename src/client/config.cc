#include "client/config.hh"
#include <cstdio>

Config::Config(std::string _filename)
    : filename(_filename)
{
    SetDefaults();
	Read();
}
Config::~Config()
{
	Write();
}

void Config::SetDefaults()
{
	SetName("Dumb Schmuck");
}

std::string Config::Name() const
{
	return _name;
}
void Config::SetName(std::string name)
{
	_name = name;
}

sf::Packet& operator<<(sf::Packet& packet, const Config& c)
{
	packet << c.Name();
	return packet;
}

sf::Packet& operator>>(sf::Packet& packet, Config& c)
{
	std::string name(1,0);
	packet >> name;
	c.SetName(name);
	return packet;
}

// I/O bullshit nobody likes

void Config::Write()
{
    FILE* fd = fopen(filename.c_str(), "wb");
	sf::Packet packet;
	packet << *this;
    std::cout << "writing config" << std::endl;
    fseek(fd, 0, SEEK_SET);
    fwrite(packet.GetData(), packet.GetDataSize(), 1, fd);
    fflush(fd);
    fclose(fd);
}

void Config::Read()
{
    FILE* fd = fopen(filename.c_str(), "rb");
	char buff[1024];
	sf::Packet packet;
	do {
		packet.Append(buff, fread(buff, 1, 1024, fd));
	} while(!feof(fd));
	if(packet.GetDataSize() > 0) {
		(void)(packet >> *this);
	}
    fclose(fd);
}