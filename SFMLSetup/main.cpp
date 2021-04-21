#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Game.h"

int main() 
{
    //Init Game engine
	Game game;

	while (game.running()) {

		game.update();

		game.render();
	}

	return 0;
}