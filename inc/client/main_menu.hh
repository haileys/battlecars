#ifndef MAIN_MENU_HH
#define MAIN_MENU_HH

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "client/ui/main_menu.hh"
#include "client/scene.hh"
#include <vector>

class MainMenu : public Scene
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
    UI::MainMenu main_menu;
    
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