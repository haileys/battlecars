#ifndef ASSET_CACHE_HH
#define ASSET_CACHE_HH

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetCache
{
    std::map<std::string, sf::Image> images;
    std::map<std::string, sf::Font> fonts;
public:
    sf::Image& Image(const std::string& name);
    sf::Font& Font(const std::string& name);
};

#endif
