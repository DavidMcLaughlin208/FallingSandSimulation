#pragma once

#include "RuleSet.h"

class DualNeighborhood : public RuleSet
{
public:
	DualNeighborhood();
	int processCell(int x, int y, int cellType) override;
	sf::Color getColorForCell(int cellType) override;
	int populateInitalCell(int x, int y) override;
	sf::Color on;
	int wrapYToBounds(int val);
	int wrapXToBounds(int val);
};

