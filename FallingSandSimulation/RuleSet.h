#pragma once

#include <SFML/Graphics.hpp>

class Simulation;

class RuleSet
{
public:
	virtual int processCell(int x, int y, int cellType, Simulation* sim) {
		return 0;
	}

	virtual sf::Color getColorForCell(int cellType) {
		return sf::Color::Black;
	}
};

