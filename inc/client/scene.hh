#ifndef SCENE_HH
#define SCENE_HH

class Scene;

#include "client/game.hh"

class Scene : public Gwen::Event::Handler
{
protected:
    Game& game;
    
public:
    Scene(Game& _game);
    virtual ~Scene();
    
    virtual void Draw() = 0;
    virtual void DrawHud() = 0;
    virtual void Tick() = 0;
    virtual bool DispatchEvent(sf::Event& ev) = 0;
};

#endif