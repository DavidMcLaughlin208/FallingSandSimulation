#include "Life.h"

Life::Life() {
}

int Life::processCell(int x, int y, int cellType)
{
	int totalRows = RuleSet::sim->unitUtils->getMatrixHeight();
	int totalCellsPerRow = RuleSet::sim->unitUtils->getMatrixWidth();
	int total = 0;
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
			total += RuleSet::sim->matrix->getCell(newX + newY * totalCellsPerRow);
		}
	}
	if (cellType == 1) {
		if (total <= 1 || total >= 4) {
			return 0;
		}
	}
	else {
		if (total == 3) {
			return 1;
		}
	}
	return cellType;
}

sf::Color Life::getColorForCell(int cellType)
{
	if (cellType == 1) {
		return sf::Color::Yellow;
	}
	else {
		return sf::Color::Black;
	}
}

int Life::populateInitalCell(int x, int y)
{
	return rand() % 2;
}
