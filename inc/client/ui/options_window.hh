#ifndef OPTIONS_WINDOW_HH
#define OPTIONS_WINDOW_HH

#include <Gwen/Controls/WindowControl.h>
#include <Gwen/Controls/Label.h>
#include <Gwen/Controls/TextBox.h>
#include <Gwen/Controls/Layout/Position.h>
#include <Gwen/Utility.h>
#include <Gwen/Events.h>

#include "client/game.hh"

namespace UI
{
    
class OptionsWindow : public Gwen::Event::Handler
{    
    Game& game;
    Gwen::Controls::Canvas* canvas;
    Gwen::Controls::WindowControl* window;

	Gwen::Controls::TextBox* nickname;
	
	Gwen::Controls::Button* apply;
	Gwen::Controls::Button* close;
    
    void apply_OnPress(Gwen::Controls::Base* sender);
    void close_OnPress(Gwen::Controls::Base* sender);
    
public:
    OptionsWindow(Game& _game, Gwen::Controls::Canvas* _canvas);
    ~OptionsWindow();
    
    void Show();
};

}

#endif