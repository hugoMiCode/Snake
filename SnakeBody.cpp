#include "SnakeBody.h"

SnakeBody::SnakeBody(sf::Texture& snake, sf::RenderWindow& window, int snake_size)
{
	enum Corps { LeftUp, UpUp, UpLeft, RightLeft, UpRight, RightUp };

	this->snake_size = snake_size;
	this->membre = 0;
    this->anim = sf::Vector2i(3, 0);

	this->sprite_tete.setTexture(snake);
	this->sprite_tete.setPosition((window.getSize().x / 2), window.getSize().y - 2 * snake_size);

	this->sprite_queue.setTexture(snake);
	this->sprite_queue.setTextureRect(sf::IntRect(3 * snake_size, 2 * snake_size, snake_size, snake_size));

	this->sprite_corps.setTexture(snake);

	this->coordX.push_front(this->sprite_tete.getPosition().x);
	this->coordY.push_front(this->sprite_tete.getPosition().y - snake_size);
	this->type.push_front(UpUp);
	this->type_queue.push_front(1);

}

void SnakeBody::gestion_corps(sf::RenderWindow& window)
{
    unsigned int taille{ (unsigned int)this->type.size() };

    switch (this->type_queue[this->type_queue.size() - 1])
    {
    case Up:
        this->sprite_queue.setTextureRect(sf::IntRect(3 * this->snake_size, 2 * this->snake_size, this->snake_size, this->snake_size));
        break;
    case Down:
        this->sprite_queue.setTextureRect(sf::IntRect(4 * this->snake_size, 3 * this->snake_size, this->snake_size, this->snake_size));
        break;
    case Left:
        this->sprite_queue.setTextureRect(sf::IntRect(3 * this->snake_size, 3 * this->snake_size, this->snake_size, this->snake_size));
        break;
    case Right:
        this->sprite_queue.setTextureRect(sf::IntRect(4 * this->snake_size, 2 * this->snake_size, this->snake_size, this->snake_size));
        break;
    }
    sprite_queue.setPosition(this->coordX[taille - 1], this->coordY[taille - 1]);

    for (unsigned int i{ 0 }; i < this->membre; i++)
    {
        switch (this->type[i])
        {
        case LeftUp:
            this->sprite_corps.setTextureRect(sf::IntRect(2 * this->snake_size, 2 * this->snake_size, this->snake_size, this->snake_size));
            break;
        case UpUp:
            sprite_corps.setTextureRect(sf::IntRect(2 * this->snake_size, this->snake_size, this->snake_size, this->snake_size));
            break;
        case UpLeft:
            sprite_corps.setTextureRect(sf::IntRect(2 * this->snake_size, 0, this->snake_size, this->snake_size));
            break;
        case RightLeft:
            sprite_corps.setTextureRect(sf::IntRect(this->snake_size, 0, this->snake_size, this->snake_size));
            break;
        case UpRight:
            sprite_corps.setTextureRect(sf::IntRect(0, 0, this->snake_size, this->snake_size));
            break;
        case RightUp:
            sprite_corps.setTextureRect(sf::IntRect(0, this->snake_size, this->snake_size, this->snake_size));
            break;
        }
        this->sprite_corps.setPosition(this->coordX[i], this->coordY[i]);

        if (this->sprite_queue.getPosition() != this->sprite_corps.getPosition())
        {
            window.draw(this->sprite_corps);
        }
    }
}

void SnakeBody::setSprite_tete(sf::Vector2f pos)
{
	this->sprite_tete.setPosition(pos);
}
void SnakeBody::setSprite_queue(sf::Vector2f pos)
{
	this->sprite_queue.setPosition(pos);
}
void SnakeBody::setSprite_corps(sf::Vector2f pos)
{
	this->sprite_corps.setPosition(pos);
}

int SnakeBody::getMembre()
{
    return this->membre;
}
sf::Vector2i SnakeBody::getAnim()
{
    return this->anim;
}
std::deque<int> SnakeBody::getcoordX()
{
    return this->coordX;
}
std::deque<int> SnakeBody::getcoordY()
{
    return this->coordY;
}

void SnakeBody::setAnim(sf::Vector2i pic)
{
    this->anim = pic;
}

void SnakeBody::setPopType()
{
    this->type.pop_back();
}
void SnakeBody::setPopType_queue()
{
    this->type_queue.pop_back();
}
void SnakeBody::setPopCoordX()
{
    this->coordX.pop_back();
}
void SnakeBody::setPopCoordY()
{
    this->coordY.pop_back();
}

void SnakeBody::setPushType(int a)
{
    this->type.push_front(a);
}
void SnakeBody::setPushType_queue(int a)
{
    this->type_queue.push_front(a);
}
void SnakeBody::setPushCoordX(int a)
{
    this->coordX.push_front(a);
}
void SnakeBody::setPushCoordY(int a)
{
    this->coordY.push_front(a);
}

void SnakeBody::show(sf::RenderWindow& window)
{
	window.draw(sprite_tete);
	window.draw(sprite_corps);
	window.draw(sprite_queue);
}