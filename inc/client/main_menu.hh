#ifndef MAIN_MENU_HH
#define MAIN_MENU_HH

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include "client/scene.hh"
#include "client/ui/server_browser.hh"
#include "client/ui/options_window.hh"
#include <vector>
#include <Gwen/UnitTest/UnitTest.h>
#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/TabControl.h>
#include <Gwen/Controls/ListBox.h>
#include <Gwen/Events.h>

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
    
    sf::Image heading_image;
    sf::Sprite heading;
    
    Gwen::Font mainButtonFont;
    Gwen::Controls::Button* serverBrowserButton;
    Gwen::Controls::Button* singlePlayerButton;
    Gwen::Controls::Button* optionsButton;
    Gwen::Controls::Button* quitButton;
    void serverBrowserButton_OnPress(Gwen::Controls::Base* sender);
    void singlePlayerButton_OnPress(Gwen::Controls::Base* sender);
    void optionsButton_OnPress(Gwen::Controls::Base* sender);
    void quitButton_OnPress(Gwen::Controls::Base* sender);
    
    UI::ServerBrowser serverBrowser;
    UI::OptionsWindow optionsWindow;
    
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
