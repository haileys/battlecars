#include "client/game.hh"
#include "client/scene.hh"
#include "client/main_menu.hh"
#include "client/single_player.hh"

Game::Game()
    : window(sf::VideoMode(1024, 768), "Battlecars"),
      view(window.GetDefaultView()),
      input(window.GetInput()),
      scene(NULL),
      nextScene(NULL),
      gwenRenderer(window),
      gwenCanvas(&gwenSkin)
{
    next_tick_at = clock.GetElapsedTime();
    
    // piece of shit gwen library initialization    
    gwenSkin.SetRender(&gwenRenderer);
    gwenSkin.Init("assets/DefaultSkin.png");
	gwenSkin.SetDefaultFont( L"assets/OpenSans.ttf", 11 );
	
	gwenCanvas.SetSize(window.GetWidth(), window.GetHeight());
	gwenCanvas.SetDrawBackground(false);
	
    gwenInput.Initialize(&gwenCanvas);
}

Game::~Game()
{
    if(scene) {
        delete scene;
    }
}

void Game::SetScene(Scene* _scene)
{
    if(scene) {
        delete scene;
    }
    scene = _scene;
}

void Game::SetSceneWhenSafe(Scene* _scene)
{
	if(nextScene) {
		delete nextScene;
	}
	nextScene = _scene;
}

void Game::Draw()
{    
    window.Clear();
    scene->Draw();    
    window.SetView(sf::View(sf::FloatRect(0, 0, window.GetWidth(), window.GetHeight())));
    scene->DrawHud();
    gwenCanvas.RenderCanvas();
    window.SetView(view);
    window.Display();
}

void Game::DispatchEvent(sf::Event& ev)
{    
    switch(ev.Type) {
        case sf::Event::Closed:
            window.Close();
            return;
        case sf::Event::Resized:
            window.Create(sf::VideoMode(ev.Size.Width, ev.Size.Height), "Battlecars");
            view = window.GetDefaultView();
        	gwenCanvas.SetSize(window.GetWidth(), window.GetHeight());
            // fall-through
        default:
            if(!scene->DispatchEvent(ev)) {
                gwenInput.ProcessMessage(ev);
            }
            break;
    }
}

void Game::Exit()
{
	window.Close();
}

void Game::Run()
{
    scene = new MainMenu(*this);
    //scene = new SinglePlayer(*this);
    
    window.UseVerticalSync(true);
    
    while(window.IsOpened()) {
    	if(nextScene) {
    		SetScene(nextScene);
    		nextScene = NULL;
    	}
        sf::Event ev;
        while(window.GetEvent(ev)) {
            DispatchEvent(ev);
        }
        float t = clock.GetElapsedTime();
        while(t > next_tick_at) {
            next_tick_at += 1.0/(double)TICKS_PER_SECOND;
            scene->Tick();
        }
        Draw();
    }
}
