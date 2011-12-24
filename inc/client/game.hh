#ifndef GAME_HH
#define GAME_HH

class Game;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <Gwen/Renderers/SFML.h>
#include <Gwen/Input/SFML.h>
#include <Gwen/Skin.h>
#include <Gwen/Skins/Simple.h>
#include <Gwen/Skins/TexturedBase.h>
#include <Gwen/UnitTest/UnitTest.h>
#include "client/scene.hh"
#include "client/asset_cache.hh"

class Game
{    
public:
    static const int TICKS_PER_SECOND = 100;
    
    sf::RenderWindow window;
    sf::View view;
    const sf::Input& input;
    sf::Clock clock;
    float next_tick_at;
    Scene* scene;
    Scene* nextScene;
    AssetCache assets;
    
    Gwen::Renderer::SFML gwenRenderer;
    Gwen::Skin::TexturedBase gwenSkin;
    Gwen::Input::SFML gwenInput;
    Gwen::Controls::Canvas gwenCanvas;
    UnitTest* gwenUnitTest;
    
    Game();
    ~Game();
    
    void SetScene(Scene* _scene);
    void SetSceneWhenSafe(Scene* _scene);
    void Run();
    void Exit();
    void Draw();
    void DispatchEvent(sf::Event& ev);
};

#endif
