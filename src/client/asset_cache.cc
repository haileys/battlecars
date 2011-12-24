#include <iostream>
#include "client/asset_cache.hh"

sf::Image& AssetCache::Image(const std::string& name)
{
    if(images.find(name) == images.end()) {
        std::cout << "Loading image " << name << std::endl;
        images[name].LoadFromFile(name);
    }    
    return images[name];
}

sf::Font& AssetCache::Font(const std::string& name)
{
    if(fonts.find(name) == fonts.end()) {
        std::cout << "Loading font " << name << std::endl;
        fonts[name].LoadFromFile(name);
    }
    return fonts[name];
}
