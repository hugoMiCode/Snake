	#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Pomme
{
public:
	Pomme(sf::Texture&, int);
	bool eat(sf::Sprite&, int);
	void setPosition(sf::Vector2f&);
	sf::Vector2f getPosition();
	sf::Vector2f update(sf::RenderWindow&, std::deque<int>&, std::deque<int>&, int, int);
	void show(sf::RenderWindow&);

private:
	int pommeX;
	int pommeY;
	sf::Sprite sprite_pomme;

};

