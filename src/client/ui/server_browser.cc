#include "client/ui/server_browser.hh"
#include "client/multi_player.hh"
#include <SFML/Network.hpp>

using namespace UI;

ServerBrowser::ServerBrowser(Game& _game, Gwen::Controls::Canvas* _canvas)
    : game(_game), canvas(_canvas)
{
    window = new Gwen::Controls::WindowControl(canvas);
    window->SetTitle("Server Browser");
    window->SetPos(160, 160);
    window->SetSize(800, 600);
    window->Hide();
    
    tabControl = new Gwen::Controls::TabControl(window);
    tabControl->Dock(Gwen::Pos::Fill);
    
    {
		Gwen::Controls::TabButton* internetButton = tabControl->AddPage(L"Internet");
		/*Gwen::Controls::Base* page = */internetButton->GetPage();
	}
	
	{
		Gwen::Controls::TabButton* lanButton = tabControl->AddPage(L"LAN");
		Gwen::Controls::Base* page = lanButton->GetPage();
		
        Gwen::Controls::Button* playSelfButton = new Gwen::Controls::Button(page);
        playSelfButton->SetText("Play on localhost");
        playSelfButton->onPress.Add(this, &ServerBrowser::playOnLocalhost);
	}
}

ServerBrowser::~ServerBrowser()
{
    delete window;
}

void ServerBrowser::Show()
{    
    window->Show();
}

void ServerBrowser::playOnLocalhost(Gwen::Controls::Base* sender)
{
    sf::IPAddress localhost("127.0.0.1");
    game.SetSceneWhenSafe(new MultiPlayer(game, localhost, 2277));
}