#include "RockPaperScissors.h"

RockPaperScissors::RockPaperScissors() {
	this->cellColors.push_back(sf::Color::Black);
	this->cellColors.push_back(sf::Color::Magenta);
	this->cellColors.push_back(sf::Color::White);
	this->cellColors.push_back(sf::Color::Yellow);
	this->cellColors.push_back(sf::Color::Red);
	this->cellColors.push_back(sf::Color::Green);
}

int RockPaperScissors::processCell(int x, int y, int cellType) {
	int totalRows = sim->unitUtils->getMatrixHeight();
	int totalCellsPerRow = sim->unitUtils->getMatrixWidth();
	int eatCount = 0;
	int targetCellType1 = cellType - 1;
	int targetCellType2 = cellType - 2;
	int targetCellCount1 = 0;
	int targetCellCount2 = 0;
	for (int modY = -1; modY <= 1; modY++) {
		for (int modX = -1; modX <= 1; modX++) {
			if (modY == 0 && modX == 0) {
				continue;
			}
			int newX = x + modX;
			int newY = y + modY;
			if (newX > totalCellsPerRow - 1) {
				newX = 0;
			}
			else if (newX < 0) {
				newX = totalCellsPerRow - 1;
			}

			if (newY > totalRows - 1) {
				newY = 0;
			}
			else if (newY < 0) {
				newY = totalRows - 1;
			}
			int neighborCellType = RuleSet::sim->matrix->getCell(newX + newY * totalCellsPerRow);
			if (cellType == -1 && neighborCellType != -1) {
				return neighborCellType;
			}

			if (targetCellType1 < 0) {
				targetCellType1 = sim->cellTypes - 1;
			}
			if (targetCellType2 < 0) {
				targetCellType2 = sim->cellTypes - 2;
			}
			if (neighborCellType == targetCellType1) {
				targetCellCount1++;
			}
			if (neighborCellType == targetCellType1) {
				targetCellCount2++;
			}
			if (targetCellCount1 > 2) {
				return targetCellType1;
			}
			if (targetCellCount2 > 2) {
				return targetCellType1;
			}
		}
	}
	return cellType;
}

sf::Color RockPaperScissors::getColorForCell(int cellType)
{
	return this->cellColors[cellType + 1];
}

int RockPaperScissors::populateInitalCell(int x, int y)
{
	return (rand() % (this->sim->cellTypes + 1)) - 1;
}
