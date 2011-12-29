#ifndef SERVER_BROWSER_HH
#define SERVER_BROWSER_HH

#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/TabControl.h>
#include <Gwen/Controls/ListBox.h>
#include <Gwen/Controls/Layout/Position.h>
#include <Gwen/Utility.h>
#include <Gwen/Events.h>

#include "client/game.hh"

class ServerBrowser : public Gwen::Event::Handler
{    
    Game& game;
    Gwen::Controls::Canvas* canvas;
    Gwen::Controls::WindowControl* window;
    Gwen::Controls::TabControl* tabControl;
    
public:
    ServerBrowser(Game& _game, Gwen::Controls::Canvas* _canvas);
    ~ServerBrowser();
    
    void Show();
    void playOnLocalhost(Gwen::Controls::Base* sender);
};

#endif