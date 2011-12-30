#include "client/player.hh"

Player::Player(Game& _game, uint32_t _id, std::string& _name, float _x, float _y, float _velocity, float _heading)
    : game(_game), id(_id), name(_name), x(_x), y(_y), velocity(_velocity), heading(_heading),
      car(game.assets.Image("assets/car.png")), label(name, game.assets.Font("assets/OpenSans.ttf"), 12)
{
    label.SetColor(sf::Color(255, 255, 255, 255));
    label_width = (int)label.GetRect().GetWidth();
    label_background = sf::Shape::Rectangle(0, 0, label_width + 8, (int)label.GetRect().GetHeight() + 6, sf::Color(0, 0, 0, 128));
}

void Player::Render(sf::RenderTarget& target, int mid_x, int mid_y)
{    
    car.SetPosition(mid_x + x, mid_y - y);
    label.SetPosition(mid_x + x - (label_width / 2), mid_y - y + 34);
    label_background.SetPosition(mid_x + x - (label_width / 2) - 4, mid_y - y + 32);
    car.SetRotation(-heading * 180.0 / M_PI);
    
    target.Draw(car);
    target.Draw(label_background);
    target.Draw(label);
}