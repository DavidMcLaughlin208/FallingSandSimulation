#include "Simulation.h"


const bool Simulation::running()
{
	return this->window->isOpen();
}

void Simulation::initWindow()
{
	this->videoMode.height = this->windowHeight;
	this->videoMode.width = this->windowWidth;
	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(144);
}

void Simulation::initializeVariables() {
	this->window = nullptr;
	this->unitUtils = new UnitUtils(this->pixelModifier, this->windowWidth, this->windowHeight);
	this->matrix = new CellularAutomaton(this->unitUtils->getMatrixWidth(), this->unitUtils->getMatrixHeight());
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
}

Simulation::Simulation()
{
	srand(time(0));
	this->initializeVariables();
	this->initWindow();
	this->populateMatrix();
	this->initTexture();
}

Simulation::~Simulation()
{
}

void Simulation::pollEvents()
{
	while (this->window->pollEvent(this->ev)) {
		switch (this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				this->window->close();
			}
			break;
		case sf::Event::MouseButtonPressed:
			break;
		default:
			break;
		}
	}
}

void Simulation::populateMatrix() {
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	for (int y = 0; y < totalRows; y++) {
		//std::cout << "newRow" << y << std::endl;
		for (int x = 0; x < totalCellsPerRow; x++) {
			this->matrix->setCell(x + y * totalCellsPerRow, rand() % 3);
		}
	}
	this->matrix->swapBuffer();
	std::cout << "Finished populating matrix" << std::endl;
}

void Simulation::updateMatrix() {
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	for (int y = 0; y < totalRows; y++) {
		//std::cout << "newRow" << y << std::endl;
		for (int x = 0; x < totalCellsPerRow; x++) {
			int currentCell = this->matrix->getCell(x + y * totalCellsPerRow);
			bool getEaten = getNeighbors(x, y, currentCell);
			if (getEaten) {
				if (currentCell == 0) {
					this->matrix->setCell(x + y * totalCellsPerRow, 2);
				}
				else {
					this->matrix->setCell(x + y * totalCellsPerRow, currentCell - 1);
				}
				
			}
			else {
				this->matrix->setCell(x + y * totalCellsPerRow, currentCell);
			}
			
		}
	}
}

bool Simulation::getNeighbors(int x, int y, int cellType) {
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	int eatCount = 0;
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
			int neighborCellType = this->matrix->getCell(newX + newY * totalCellsPerRow);
			if (cellType == 0 && neighborCellType == 2) {
				eatCount++;
			}
			else if (cellType == 1 && neighborCellType == 0) {
				eatCount++;
			}
			else if (cellType == 2 && neighborCellType == 1) {
				eatCount++;
			}
			if (eatCount > 2) {
				return true;
			}
		}
	}
	return false;
}

void Simulation::initTexture() {
	this->texture->create(unitUtils->getMatrixWidth(), unitUtils->getMatrixHeight());
	this->pixels = new std::vector<sf::Uint8>(this->unitUtils->getMatrixWidth() * this->unitUtils->getMatrixHeight() * this->unitUtils->getPixelSize());
	this->updateTexture();
}

void Simulation::updateTexture() {
	std::vector<sf::Uint8> pixelRef = *this->pixels;
	int totalRows = this->unitUtils->getMatrixHeight();
	int totalCellsPerRow = this->unitUtils->getMatrixWidth();
	for (int y = 0; y < totalRows; y++) {
		//std::cout << "newRow" << y << std::endl;
		for (int x = 0; x < totalCellsPerRow; x++) {

			int actualX = x * this->unitUtils->getPixelSize();
			int actualY = y * totalCellsPerRow * this->unitUtils->getPixelSize();
			int cellType = this->matrix->getCell(x + y * totalCellsPerRow);
			sf::Color color;
			if (cellType > 2 || cellType < 0) {
				std::cout << "Broken";
			}
			if (cellType == 0) {
				color = sf::Color::Blue;
			} 
			else if (cellType == 1) {
				color = sf::Color::Red;
			}
			else if (cellType == 2) {
				color = sf::Color::Green;
			}
			pixelRef[actualX + actualY] = color.r;
			pixelRef[actualX + actualY + 1] = color.g;
			pixelRef[actualX + actualY + 2] = color.b;
			pixelRef[actualX + actualY + 3] = color.a;
		}
	}
	this->sprite->setTexture(*this->texture);
	sf::Uint8* startOfArray = &pixelRef[0];
	this->texture->update(startOfArray);
	this->sprite->setScale(this->unitUtils->getPixelModifier(), this->unitUtils->getPixelModifier());
}

void Simulation::update()
{
	this->pollEvents();

	this->updateMatrix();

	this->updateTexture();

	this->matrix->swapBuffer();
}

void Simulation::render()
{
	this->window->clear();

	this->window->draw(*this->sprite);

	this->window->display();
}


