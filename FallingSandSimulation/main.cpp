#include <iostream>
#include <string>
#include <chrono>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Game.h"
#include "Simulation.h"

int main() 
{
    //Init Game engine
	//Game game;
	Simulation sim;

	//while (game.running()) {
	//	//auto startUpdate = std::chrono::high_resolution_clock::now();
	//	game.update();
	//	//auto elapsedUpdate = std::chrono::high_resolution_clock::now() - startUpdate;
	//	//std::cout << "Update took: " << elapsedUpdate / std::chrono::milliseconds(1) << " ms" << std::endl;
	//	//auto startRender = std::chrono::high_resolution_clock::now();
	//	game.render();
	//	//auto elapsed = std::chrono::high_resolution_clock::now() - startRender;
	//	//std::cout << "Render took: " << elapsed/std::chrono::milliseconds(1) << " ms" <<  std::endl;
	//}

	int waitTime = 50;

	while (sim.running()) {
		auto startUpdate = std::chrono::high_resolution_clock::now();
		sim.update();
		sim.render();
		auto elapsedUpdate = std::chrono::high_resolution_clock::now() - startUpdate;

		int timeElapsed = elapsedUpdate / std::chrono::milliseconds(1);

		if (timeElapsed < waitTime) {
			//std::cout << "Sleeping" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime - timeElapsed));
		}
		
	}

	return 0;
}