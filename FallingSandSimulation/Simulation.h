#pragma once

#include <iostream>
#include <vector>
#include "UnitUtils.h"
#include "CellularAutomaton.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <chrono>
#include <vector>


class Simulation
{
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Vector2i mousePosWindow;
	UnitUtils* unitUtils;
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 800;
	int pixelModifier = 6;
	sf::Texture* texture;
	sf::Sprite* sprite;
	std::vector<sf::Uint8>* pixels;
	CellularAutomaton* matrix;
	bool mouseDown = false;
	sf::Shader shader;
public:
	Simulation();
	~Simulation();
	void pollEvents();
	void initTexture();
	void updateTexture();
	void updateMousePositions();
	void update();
	void render();
	const bool running();
	void initWindow();
	void initializeVariables();
	void populateMatrix();
	void updateMatrix();
	bool getNeighbors(int x, int y, int cellType);
	void click();
};

