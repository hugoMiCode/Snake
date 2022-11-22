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

class SnakeBody
{
public:
	SnakeBody(sf::Texture&, sf::RenderWindow&, int);
	void show(sf::RenderWindow&);
	int getMembre();
	sf::Vector2i getAnim();
	std::deque<int> getcoordX();
	std::deque<int> getcoordY();


	void setAnim(sf::Vector2i);

	void setPopType();
	void setPopType_queue();
	void setPopCoordX();
	void setPopCoordY();

	void setPushType(int);
	void setPushType_queue(int);
	void setPushCoordX(int);
	void setPushCoordY(int);

	void gestion_corps(sf::RenderWindow&);
	void setSprite_tete(sf::Vector2f);
	void setSprite_queue(sf::Vector2f);
	void setSprite_corps(sf::Vector2f);

private:
	int membre, snake_size;
	sf::Sprite sprite_queue, sprite_tete, sprite_corps;
	std::deque<int> coordX{}, coordY{}, type{}, type_queue{};
	sf::Vector2i anim;

};

enum Dir { Up, Down, Left, Right };
enum Corps { LeftUp, UpUp, UpLeft, RightLeft, UpRight, RightUp };

