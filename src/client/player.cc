#include "client/player.hh"

Player::Player(Game& _game, uint32_t _id, std::string& _name, float _x, float _y, float _velocity, float _heading)
    : game(_game), id(_id), name(_name), x(_x), y(_y), velocity(_velocity), heading(_heading),
      car(game.assets.Image("assets/car.png")), label(name, game.assets.Font("assets/UbuntuMono-R.ttf"), 14)
{
    label.SetColor(sf::Color(0, 0, 0, 255));
    label_width = (int)label.GetRect().GetWidth();
}