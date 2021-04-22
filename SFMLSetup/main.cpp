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
		auto start = std::chrono::high_resolution_clock::now();
		game.update();

		game.render();
		auto elapsed = std::chrono::high_resolution_clock::now() - start;
		std::cout << "Frame took: " << elapsed/std::chrono::milliseconds(1) << " ms" <<  std::endl;
	}

	return 0;
}