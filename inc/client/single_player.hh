#ifndef SINGLE_PLAYER_HH
#define SINGLE_PLAYER_HH

#include "client/scene.hh"

class SinglePlayer : public Scene
{
    sf::Image background_image;
    sf::Sprite background;
    sf::Sprite car;
    
    sf::String coords;
    
    double targetVelocity, velocity, heading;
    double x, y;
    
public:
    SinglePlayer(Game& _game);
    ~SinglePlayer();
    virtual void Draw();
    virtual void DrawHud();
    virtual void Tick();
    virtual bool DispatchEvent(sf::Event& ev);
};

#endif