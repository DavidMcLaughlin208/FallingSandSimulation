#pragma once

#include <SFML/Graphics.hpp>

class Simulation;

class RuleSet
{
public:
	virtual int processCell(int x, int y, int cellType) {
		return 0;
	}

	virtual sf::Color getColorForCell(int cellType) {
		return sf::Color::Black;
	}

	virtual int populateInitalCell(int x, int y) {
		return 0;
	}

	Simulation* sim;
	int sliderVal1;
	int sliderVal2;
	int sliderVal3;
	int sliderVal4;
};

