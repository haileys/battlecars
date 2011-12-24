#ifndef MAIN_MENU_HH
#define MAIN_MENU_HH

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "client/scene.hh"
#include <vector>
#include <Gwen/Events.h>

class MainMenu : public Scene, public Gwen::Event::Handler
{
    struct Car
    {
        sf::Sprite sprite;
        float x, y, r, targetRotation, a;
        bool adjusted;

        Car(sf::Image& image, float _x, float _y, float _r);
        void Draw(sf::RenderTarget& target);
    };
          
    sf::Image background_image;
    sf::Sprite background;
    
    sf::String heading;
    Gwen::Controls::Button* singlePlayerButton;
    Gwen::Controls::Button* quitButton;
    void singlePlayerButton_OnPress(Gwen::Controls::Base* sender);
    void quitButton_OnPress(Gwen::Controls::Base* sender);
    
    std::vector<Car> cars;
    
public:    
    MainMenu(Game& _game);
    virtual ~MainMenu();
    virtual void Draw();
    virtual void DrawHud();
    virtual void Tick();
    virtual bool DispatchEvent(sf::Event& ev);
};

#endif
