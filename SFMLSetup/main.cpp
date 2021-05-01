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
		auto startUpdate = std::chrono::high_resolution_clock::now();
		game.update();
		auto elapsedUpdate = std::chrono::high_resolution_clock::now() - startUpdate;
		std::cout << "Update took: " << elapsedUpdate / std::chrono::milliseconds(1) << " ms" << std::endl;
		auto startRender = std::chrono::high_resolution_clock::now();
		game.render();
		auto elapsed = std::chrono::high_resolution_clock::now() - startRender;
		std::cout << "Render took: " << elapsed/std::chrono::milliseconds(1) << " ms" <<  std::endl;
	}

	return 0;
}