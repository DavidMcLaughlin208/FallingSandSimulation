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
	this->matrix = new CellularAutomaton(this->unitUtils->convertToMatrix(this->windowWidth), this->unitUtils->convertToMatrix(this->windowHeight));
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
}

Simulation::Simulation()
{
	this->initializeVariables();
	this->initWindow();
	//this->initVertexArray();
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

void Simulation::initTexture() {
	this->texture->create(unitUtils->convertToMatrix(this->windowWidth), unitUtils->convertToMatrix(this->windowHeight));
	this->pixels = new std::vector<sf::Uint8>(this->unitUtils->convertToMatrix(this->windowWidth) * this->unitUtils->convertToMatrix(this->windowHeight) * this->unitUtils->getPixelSize());
	//this->updateTexture();
}

void Simulation::update()
{
	this->pollEvents();
}

void Simulation::render()
{
	this->window->clear();



	this->window->display();
}


