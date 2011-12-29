#include "client/main_menu.hh"
#include "client/single_player.hh"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <SFML/System.hpp>

static std::string car_colours[] = { "assets/cars/blue.png", "assets/cars/red.png", "assets/cars/orange.png", "assets/cars/purple.png" };

MainMenu::MainMenu(Game& _game)
    : Scene(_game), serverBrowser(_game, &_game.gwenCanvas)
{
    background_image.LoadFromFile("assets/bg.png");
    background_image.SetSmooth(false);
    background = sf::Sprite(background_image);
    background.Move(-100, -99);
    
    heading_image.LoadFromFile("assets/header.png");
    heading_image.SetSmooth(false);
    heading = sf::Sprite(heading_image);
    heading.SetPosition(-10, 84);
    heading.SetColor(sf::Color(255,255,255,0));
    
    mainButtonFont.size = 18;
    
    serverBrowserButton = new Gwen::Controls::Button(&game.gwenCanvas);
    serverBrowserButton->SetText("Server Browser");
    serverBrowserButton->SetFont(&mainButtonFont);
    serverBrowserButton->SetPadding(Gwen::Padding(8, 9, 8, 11));
    serverBrowserButton->SizeToContents();
    serverBrowserButton->SetPos(40, 200);
    serverBrowserButton->onPress.Add(this, &MainMenu::serverBrowserButton_OnPress);
    
    singlePlayerButton = new Gwen::Controls::Button(&game.gwenCanvas);
    singlePlayerButton->SetText("Play Singleplayer");
    singlePlayerButton->SetFont(&mainButtonFont);
    singlePlayerButton->SetPadding(Gwen::Padding(8, 8, 8, 8));
    singlePlayerButton->SizeToContents();
    singlePlayerButton->SetPos(40, 240);
    singlePlayerButton->onPress.Add(this, &MainMenu::singlePlayerButton_OnPress);
    
    quitButton = new Gwen::Controls::Button(&game.gwenCanvas);
    quitButton->SetText("Quit");
    quitButton->SetFont(&mainButtonFont);
    quitButton->SetPadding(Gwen::Padding(8, 8, 8, 8));
    quitButton->SizeToContents();
    quitButton->SetPos(40, 280);
    quitButton->onPress.Add(this, &MainMenu::quitButton_OnPress);
    
    float w = game.window.GetWidth(), h = game.window.GetHeight();
    for(int i = 0; i < 4; i++) {
        cars.push_back(Car(game.assets.Image(car_colours[i]), sf::Randomizer::Random(0.0, w), sf::Randomizer::Random(0.0, h), 0.0f));
    }
}

void MainMenu::serverBrowserButton_OnPress(Gwen::Controls::Base* sender)
{
    serverBrowser.Show();
    
    /*
    serverBrowser = new Gwen::Controls::WindowControl(&game.gwenCanvas);
    serverBrowser->SetTitle("Server Browser");
    serverBrowser->SetPos(160, 160);
    serverBrowser->SetSize(800, 600);
    serverBrowser->SetDeleteOnClose(true);
    
    new UnitTest(serverBrowser);
    
    Gwen::Controls::ListBox* serverList = new Gwen::Controls::ListBox(serverBrowser);
    serverList->SetBounds(10, 10, 200, 200);
    serverList->AddItem(L"127.0.0.1");
    */
}

void MainMenu::singlePlayerButton_OnPress(Gwen::Controls::Base* sender)
{
	game.SetSceneWhenSafe(new SinglePlayer(game));
}

void MainMenu::quitButton_OnPress(Gwen::Controls::Base* sender)
{
	game.Exit();
}

MainMenu::~MainMenu()
{
	delete quitButton;
    quitButton = NULL;
	delete singlePlayerButton;
    singlePlayerButton = NULL;
	delete serverBrowserButton;
    singlePlayerButton = NULL;
}

MainMenu::Car::Car(sf::Image& image, float _x, float _y, float _r)
    : x(_x), y(_y), r(_r), targetRotation(_r), a(0), adjusted(false)
{    
    sprite.SetImage(image);
    sprite.SetCenter(32, 32);
    sprite.SetColor(sf::Color(255, 255, 255, a));
}

void MainMenu::Car::Draw(sf::RenderTarget& target)
{
    sprite.SetPosition(x, y);
    sprite.SetRotation(-r);
    sprite.SetColor(sf::Color(255, 255, 255, a));
    target.Draw(sprite);
}

void MainMenu::Tick()
{
	if(heading.GetColor().a < 255) {
		sf::Color hc = heading.GetColor();
		heading.SetColor(sf::Color(hc.r, hc.g, hc.b, hc.a + 1));
	}
    for(std::vector<Car>::iterator car = cars.begin(); car != cars.end(); ++car) {
        car->x += 2 * sin(car->r * M_PI / 180.0);
        car->y -= 2 * cos(car->r * M_PI / 180.0);
        
        car->targetRotation += sf::Randomizer::Random(-5.0f, 5.0f) + 40.0f * cos(car->y * M_PI / 180.0);
        
        if(car->r < car->targetRotation - 0.5) {
            car->r += 0.5;
        } else if(car->r > car->targetRotation + 0.5) {
            car->r -= 0.5;
        }
        
        if(car->y < -64) {
            car->y = game.window.GetHeight() + 64;
        } else if(car->y > game.window.GetHeight() + 64) {
            car->y = -64;
        }
        if(car->x < -64) {
            car->x = game.window.GetWidth() + 64;
        } else if(car->x > game.window.GetWidth() + 64) {
            car->x = -64;
        }
        
        if(car->a < 255) {
            car->a += 1;
        }
    }
}

bool MainMenu::DispatchEvent(sf::Event& ev)
{
    return false;
}

void MainMenu::DrawHud()
{
	game.window.Draw(heading);
}

void MainMenu::Draw()
{
    game.window.Draw(background);
    for(std::vector<Car>::iterator car = cars.begin(); car != cars.end(); ++car) {
        car->Draw(game.window);
    }
}
