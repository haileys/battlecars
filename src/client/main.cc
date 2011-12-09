#include "client/game.hh"
#include <cstdlib>
#include <SFML/System.hpp>

int main()
{
    sf::Randomizer::SetSeed(time(NULL));
    Game game;
    game.Run();
}