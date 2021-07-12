#pragma once

#include <vector>

#include "RuleSet.h"
#include "Simulation.h"

class RockPaperScissors : public RuleSet
{
private:
	std::vector <sf::Color> cellColors;
public:
	RockPaperScissors();
	int processCell(int x, int y, int cellType, Simulation* sim) override;
	sf::Color getColorForCell(int cellType) override;

};

