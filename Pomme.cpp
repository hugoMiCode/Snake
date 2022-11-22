#include "Pomme.h"


Pomme::Pomme(sf::Texture& snake, int snake_size)
{
	sprite_pomme.setTexture(snake);
	sprite_pomme.setTextureRect(sf::IntRect(0, 192, snake_size, snake_size));
	sprite_pomme.setPosition(2 * snake_size, 7 * snake_size);
	this->sprite_pomme = sprite_pomme;
}

bool Pomme::eat(sf::Sprite& sprite_tete, int snake_size)
{
	return ((std::abs((sprite_tete.getPosition().x + snake_size / 2) - (this->sprite_pomme.getPosition().x + snake_size / 2)) < snake_size &&
		std::abs((sprite_tete.getPosition().y + snake_size / 2) - (this->sprite_pomme.getPosition().y + snake_size / 2)) < snake_size));

}
sf::Vector2f Pomme::update(sf::RenderWindow& window, std::deque<int>& coordX, std::deque<int>& coordY, int snake_size, int membre)
{
    bool pomme{ false };

    while (!pomme)
    {
        this->pommeX = rand() % (0, window.getSize().x / snake_size);
        this->pommeY = rand() % (0, window.getSize().y / snake_size);
        pomme = true;

        for (unsigned int i{ 0 }; i < membre; i++)
        {
            if (coordX[i] == this->pommeX * snake_size && coordY[i] == this->pommeY * snake_size)
            {
                pomme = false;
                break;
            }
        }
    }
    return (sf::Vector2f(pommeX, pommeY));
    //sprite_pomme.setPosition(this->pommeX * snake_size, this->pommeY * snake_size);
}

void Pomme::show(sf::RenderWindow& window)
{
    window.draw(this->sprite_pomme);
}

void Pomme::setPosition(sf::Vector2f& pos)
{
	this->pommeX = pos.x;
	this->pommeY = pos.y;
}

sf::Vector2f Pomme::getPosition()
{
    sf::Vector2f coord;
    coord.x = this->pommeX;
    coord.y = this->pommeY;

    return coord;
}