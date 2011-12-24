#include "client/single_player.hh"
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdio>
#include <Gwen/Skin.h>
#include <Gwen/Skins/Simple.h>
#include <Gwen/Skins/TexturedBase.h>
#include <Gwen/UnitTest/UnitTest.h>

SinglePlayer::SinglePlayer(Game& _game)
    :   Scene(_game), targetVelocity(0), velocity(0), heading(0), x(0), y(0)
{
    background_image.LoadFromFile("assets/bg2.png");
    background_image.SetSmooth(false);
    background = sf::Sprite(background_image);
    background.Move(-100, -99);
    
    car = sf::Sprite(game.assets.Image("assets/car.png"));
    car.SetCenter(32, 32);
    
    coords = sf::String("", game.assets.Font("assets/UbuntuMono-R.ttf"), 24);
    coords.SetColor(sf::Color(0, 0, 0, 255));
}

SinglePlayer::~SinglePlayer()
{
}

void SinglePlayer::Tick()
{
    if(game.input.IsKeyDown(sf::Key::Up)) {
        targetVelocity = 450;
        if(velocity < 0) velocity = 0;
    } else if(game.input.IsKeyDown(sf::Key::Down)) {
        targetVelocity = -300;
        if(velocity > 0) velocity = 0;
    } else {
        targetVelocity = 0;
    }
    if(game.input.IsKeyDown(sf::Key::Right)) {
        heading += 1/(double)Game::TICKS_PER_SECOND * 0.015 * velocity;
    } else if(game.input.IsKeyDown(sf::Key::Left)) {
        heading -= 1/(double)Game::TICKS_PER_SECOND * 0.015 * velocity;
    }
    if(velocity != targetVelocity) {
        if(velocity > targetVelocity) {
            velocity -= 3;
        } else {
            velocity += 3;
        }
    }
    x += 1/(double)Game::TICKS_PER_SECOND * velocity * sin(heading);
    y += 1/(double)Game::TICKS_PER_SECOND * velocity * cos(heading);
    game.view.SetCenter(sf::Vector2f(game.window.GetWidth() / 2.0 + x, game.window.GetHeight() / 2.0 - y));
    game.window.SetView(game.view);
}

void SinglePlayer::DrawHud()
{    
    char coords_buff[64];
    sprintf(coords_buff, "(%d, %d), %d\n%.2f km/h", (int)x, (int)y, (int)(-heading * 180.0 / M_PI) % 360, (velocity / 15.0) * 3.6);
    coords.SetText(sf::Unicode::Text(coords_buff));
    coords.SetPosition(16, 8);
    game.window.Draw(coords);
}

void SinglePlayer::Draw()
{
    int cx = (int)(game.window.GetWidth() / 2.0 + x);
    int cy = (int)(game.window.GetHeight() / 2.0 - y);
    cx /= background.GetSize().x;
    cx *= background.GetSize().x;
    cy /= background.GetSize().y;
    cy *= background.GetSize().y;
    int y_factor = (game.window.GetHeight() / background.GetSize().y) + 1;
    int x_factor = (game.window.GetWidth() / background.GetSize().x) + 1;
    
    for(int j = -y_factor; j <= y_factor; j++) {
        for(int i = -x_factor; i <= x_factor; i++) {
            background.SetPosition(cx + i * background.GetSize().x, cy + j * background.GetSize().y);
            game.window.Draw(background);
        }
    }
    
    float deg = -heading * 180.0 / M_PI;
    car.SetPosition(game.window.GetWidth() / 2.0 + x, game.window.GetHeight() / 2.0 - y);
    car.SetRotation(deg);
    game.window.Draw(car);
}

bool SinglePlayer::DispatchEvent(sf::Event& ev)
{
    return false;
}
