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
#include <unordered_map>


class Simulation
{
private:
	//Simulation(const Simulation&) = default;
	//Simulation& operator=(const Simulation&) = default;
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Vector2i mousePosWindow;
	UnitUtils* unitUtils;
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 800;
	int pixelModifier = 3;
	sf::Texture* texture;
	sf::Sprite* sprite;
	std::vector<sf::Uint8>* pixels;
	CellularAutomaton* matrix;
	bool mouseDown = false;
	sf::Shader shader;
	int count = 0;
	std::unordered_map<int, sf::Color> typeToColorMap;
	std::unordered_map<int, int> rulesMap;
	bool threads = true;
	int threadCount;
	int cellTypes = 4;
	std::vector <sf::Color> cellColors;
public:
	Simulation();
	~Simulation();
	void pollEvents();
	void initTexture();
	void updateTexture();
	void updateTextureColumn(int start, int end);
	void updateMousePositions();
	void update();
	void render();
	const bool running();
	void initWindow();
	void initializeVariables();
	void populateMatrix();
	void updateMatrix();
	void updateMatrixColumn(int start, int end);
	int getNeighbors(int x, int y, int cellType);
	void click();
};

