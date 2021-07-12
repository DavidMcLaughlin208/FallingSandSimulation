#pragma once

#include "RuleSet.h"
#include "Simulation.h"

class Life : public RuleSet
{
private: 

public:
	Life();
	int processCell(int x, int y, int cellType) override;
	sf::Color getColorForCell(int cellType) override;
	int populateInitalCell(int x, int y) override;
};

