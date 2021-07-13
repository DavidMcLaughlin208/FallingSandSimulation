#pragma once

#include <iostream>
#include <vector>
#include "UnitUtils.h"
#include "CellularAutomaton.h"
#include "RuleSet.h"
#include "RockPaperScissors.h"
#include "PerlinNoise.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <chrono>
#include <vector>
#include <unordered_map>

class RuleSet;
class RockPaperScissors;

class Simulation
{
private:
	//Simulation(const Simulation&) = default;
	//Simulation& operator=(const Simulation&) = default;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Vector2i mousePosWindow;
	unsigned int windowWidth = 1280;
	unsigned int windowHeight = 800;
	int pixelModifier = 4;
	sf::Texture* texture;
	sf::Sprite* sprite;
	std::vector<sf::Uint8>* pixels;
	bool mouseDown = false;
	sf::Shader shader;
	int count = 0;
	bool threads = true;
	int threadCount;
	
public:
	Simulation(RuleSet* ruleSet_);
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
	//void updateMatrix();
	void updateMatrixColumn(int start, int end);
	void click();

	sf::RenderWindow* window;
	UnitUtils* unitUtils;
	RuleSet* ruleSet;
	int cellTypes = 4;
	CellularAutomaton* matrix;
	PerlinNoise* perlinNoise;
};

