#ifndef CONFIG_HH
#define CONFIG_HH

#include <SFML/Network.hpp>
#include <iostream>

class Config
{    
	std::string filename;
	std::string _name;
	
public:
	Config(std::string _filename);
	~Config();
	
	void SetDefaults();
	
	std::string Name() const;
	void SetName(std::string name);
	
	void Write();	
	void Read();
};

sf::Packet& operator<<(sf::Packet& packet, const Config& c);
sf::Packet& operator>>(sf::Packet& packet, Config& c);

#endif