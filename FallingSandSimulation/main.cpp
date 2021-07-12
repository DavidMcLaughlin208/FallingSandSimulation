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
#include "RuleSet.h"
#include "Life.h"
#include "DualNeighborhood.h"
#include "Slider.h"

int main() 
{
    //Init Game engine
	//Game game;
	RuleSet* ruleSet = new DualNeighborhood();
	Simulation sim(ruleSet);

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

	Slider timeScale(20, 20);
	timeScale.create(0, 1000);
	timeScale.setSliderPercentValue(50);
	int waitTime = 100;
	int waitAccumulator = 0;

	while (sim.running()) {
		auto startUpdate = std::chrono::high_resolution_clock::now();

		sim.window->clear();
		if (waitAccumulator > waitTime) {
			sim.update();
			waitAccumulator = 0;
		}
		
		sim.render();

		waitTime = timeScale.maxValue - timeScale.getSliderValue();
		timeScale.draw(*(sim.window));
		sim.window->display();

		auto elapsedUpdate = std::chrono::high_resolution_clock::now() - startUpdate;

		int timeElapsed = elapsedUpdate / std::chrono::milliseconds(1);
		waitAccumulator += timeElapsed;

		/*if (timeElapsed < ) {
			std::cout << "Sleeping" << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(waitTime - timeElapsed));
		}*/

		//std::cout << timeElapsed << std::endl;
		
	}

	return 0;
}