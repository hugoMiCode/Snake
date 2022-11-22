#pragma region includes
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
#pragma endregion includes

// bug dequeu out of range

#pragma region variables
sf::RenderWindow window, winOver;
sf::RectangleShape bordures;
sf::Texture snake;
sf::Sprite sprite_tete, sprite_pomme, sprite_corps, sprite_queue;
sf::Vector2i anim(3, 0);
sf::Clock clock_snake;
int const speed_snake{ 5 }, snake_size{ 64 };
enum Dir { Up, Down, Left, Right };
enum Corps { LeftUp, UpUp, UpLeft, RightLeft, UpRight, RightUp };
int clavier{ Up }, direction{ Up }, direction_prec{ Up }, membre{ 0 }, snakeX, snakeY, pommeX, pommeY;
std::deque<int> coordX{}, coordY{}, type{}, type_queue{};

#pragma endregion variables

#pragma region prototypes
void gestion_clavier(bool&);
void gestion_direction();
void gestion_pomme();
void gestion_corps();
void game_over();
void load();
#pragma endregion prototypes


int main()
{

    load();


    coordX.push_front(sprite_tete.getPosition().x);
    coordY.push_front(sprite_tete.getPosition().y - snake_size);
    type.push_front(UpUp);
    type_queue.push_front(1);


    //Pomme pomme(snake, snake_size);


    bool dead{ false };
    
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            { 
                window.close(); 
                if (winOver.isOpen())
                { winOver.close(); }
            } 
        }

        if (dead)
        {
            game_over();
        }
        else {
            snakeX = sprite_tete.getPosition().x;
            snakeY = sprite_tete.getPosition().y;
            pommeX = sprite_pomme.getPosition().x;
            pommeY = sprite_pomme.getPosition().y;

            gestion_clavier(dead);
            gestion_direction();
            gestion_pomme();

            window.clear();
            window.draw(bordures);
            gestion_corps();

            sprite_tete.setTextureRect(sf::IntRect(anim.x * snake_size, anim.y * snake_size, snake_size, snake_size));
            window.draw(sprite_tete);
            window.draw(sprite_queue);
            window.draw(sprite_pomme);
        }

        window.display();
    }

    return 0;
}

void load()
{

    window.create(sf::VideoMode(16 * snake_size, 9 * snake_size), "Snake");
    window.setVerticalSyncEnabled(true);

    if (!snake.loadFromFile("snake.png"))
    {
        std::cout << "Erreur de chargement du snake !" << std::endl;
    }

    snake.setSmooth(true);

    sprite_tete.setTexture(snake);
    sprite_tete.setPosition((window.getSize().x / 2), window.getSize().y - 2 * snake_size);

    sprite_queue.setTexture(snake);
    sprite_queue.setTextureRect(sf::IntRect(3 * snake_size, 2 * snake_size, snake_size, snake_size));

    sprite_corps.setTexture(snake);

    sprite_pomme.setTexture(snake);
    sprite_pomme.setTextureRect(sf::IntRect(0, 192, snake_size, snake_size));
    sprite_pomme.setPosition(2 * snake_size, 7 * snake_size);

    bordures.setSize(sf::Vector2f(window.getSize().x - 10, window.getSize().y - 10));
    bordures.setPosition(5, 5);
    bordures.setFillColor(sf::Color(85, 107, 47));
    bordures.setOutlineThickness(15);
    bordures.setOutlineColor(sf::Color(139, 69, 19));
}

void gestion_clavier(bool& dead)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        clavier = Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        clavier = Down;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
        clavier = Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        clavier = Right;
    } 

    if (snakeX <= -5) {
        //sprite_tete.setPosition(0, snakeY);
        dead = true;
    } 
    else if (snakeY <= -5) {
        //sprite_tete.setPosition(snakeX, 0);
        dead = true;
    }
    else if ((unsigned int)snakeX >= window.getSize().x - snake_size + 5) {
        //sprite_tete.setPosition(window.getSize().x - snake_size, snakeY);
        dead = true;
    }
    else if ((unsigned int)snakeY >= window.getSize().y - snake_size + 5) {
        //sprite_tete.setPosition(snakeX, window.getSize().y - snake_size);
        dead = true;
    }

    for (unsigned int i{ 0 }; i < type.size(); i++)
    {
        if (snakeX == coordX[i] && snakeY == coordY[i])
        {
            dead = true;
        }
    }
}
void gestion_direction()
{
    if (clock_snake.getElapsedTime().asMilliseconds() > speed_snake * 50)
    {

        if (snakeX % snake_size == 0)
        {
            if (clavier == Up && direction != Down) {
                direction = Up;
            }
            else if (clavier == Down && direction != Up) {
                direction = Down;
            }
        }
        if (snakeY % snake_size == 0)
        {
            if (clavier == Left && direction != Right) {
                direction = Left;
            }
            else if (clavier == Right && direction != Left) {
                direction = Right;
            }
        }
    
        if (membre == type.size() - 1)
        {
            type.pop_back();
            type_queue.pop_back();
            coordX.pop_back();
            coordY.pop_back();
        }

        if (direction == Up) {
            sprite_tete.move(0, -snake_size);
            anim = sf::Vector2i(3, 0);

            type_queue.push_front(Up);

            if (direction_prec == Up) {
                type.push_front(UpUp);
            } else if (direction_prec == Left) {
                type.push_front(RightUp);
            } else if (direction_prec == Right) {
                type.push_front(LeftUp);
            }

            direction_prec = Up;
        }
        else if (direction == Down) {
            sprite_tete.move(0, snake_size);
            anim = sf::Vector2i(4, 1);

            type_queue.push_front(Down);

            if (direction_prec == Down) {
                type.push_front(UpUp);
            }
            else if (direction_prec == Left) {
                type.push_front(UpRight);
            }
            else if (direction_prec == Right) {
                type.push_front(UpLeft);
            }

            direction_prec = Down;
        }
        else if (direction == Left) {
            sprite_tete.move(-snake_size, 0);
            anim = sf::Vector2i(3, 1);

            type_queue.push_front(Left);

            if (direction_prec == Left) {
                type.push_front(RightLeft);
            }
            else if (direction_prec == Up) {
                type.push_front(UpLeft);
            }
            else if (direction_prec == Down) {
                type.push_front(LeftUp);
            }

            direction_prec = Left;
        }
        else if (direction == Right) {
            sprite_tete.move(snake_size, 0);
            anim = sf::Vector2i(4, 0);

            type_queue.push_front(Right);

            if (direction_prec == Right) {
                type.push_front(RightLeft);
            }
            else if (direction_prec == Down) {
                type.push_front(RightUp);
            } 
            else if (direction_prec == Up) {
                type.push_front(UpRight);
            }

            direction_prec = Right;
        }


        coordX.push_front(snakeX);
        coordY.push_front(snakeY);

        clock_snake.restart();
    }

}
void gestion_pomme()
{
    pommeX = rand() % (0, window.getSize().x / snake_size);
    pommeY = rand() % (0, window.getSize().y / snake_size);

    if ((std::abs((sprite_tete.getPosition().x + snake_size / 2) - (sprite_pomme.getPosition().x + snake_size / 2)) < snake_size &&
        std::abs((sprite_tete.getPosition().y + snake_size / 2) - (sprite_pomme.getPosition().y + snake_size / 2)) < snake_size)) {
        bool pomme{ false };
        
        while (!pomme)
        {
            pomme = true;

            for (unsigned int i{ 0 }; i < membre; i++)
                if (coordX[i] == pommeX * snake_size && coordY[i] == pommeY * snake_size) {
                    pomme = false;
                    break;
                }
        }
        membre++;
        sprite_pomme.setPosition(pommeX * snake_size, pommeY * snake_size);
    }
}
void gestion_corps()
{
    unsigned int taille{ (unsigned int)type.size() };

    switch (type_queue[type_queue.size() - 1])
    {
    case Up:
        sprite_queue.setTextureRect(sf::IntRect(3 * snake_size, 2 * snake_size, snake_size, snake_size));
        break;
    case Down:
        sprite_queue.setTextureRect(sf::IntRect(4 * snake_size, 3 * snake_size, snake_size, snake_size));
        break;
    case Left:
        sprite_queue.setTextureRect(sf::IntRect(3 * snake_size, 3 * snake_size, snake_size, snake_size));
        break;
    case Right:
        sprite_queue.setTextureRect(sf::IntRect(4 * snake_size, 2 * snake_size, snake_size, snake_size));
        break;
    }
    sprite_queue.setPosition(coordX[taille - 1], coordY[taille - 1]);

    for (unsigned int i{ 0 }; i < membre; i++)
    {
        switch(type[i])
        {
        case LeftUp:
            sprite_corps.setTextureRect(sf::IntRect(2 * snake_size, 2 * snake_size, snake_size, snake_size));
            break;
        case UpUp:
            sprite_corps.setTextureRect(sf::IntRect(2 * snake_size, snake_size, snake_size, snake_size));
            break;
        case UpLeft:
            sprite_corps.setTextureRect(sf::IntRect(2 * snake_size, 0, snake_size, snake_size));
            break;
        case RightLeft:
            sprite_corps.setTextureRect(sf::IntRect(snake_size, 0, snake_size, snake_size));
            break;
        case UpRight:
            sprite_corps.setTextureRect(sf::IntRect(0, 0, snake_size, snake_size));
            break;
        case RightUp:
            sprite_corps.setTextureRect(sf::IntRect(0, snake_size, snake_size, snake_size));
            break;
        }
        sprite_corps.setPosition(coordX[i], coordY[i]);

        if (sprite_queue.getPosition() != sprite_corps.getPosition())
        {
            window.draw(sprite_corps);
        }
    }
}

void game_over()
{
    sf::Font font;
    sf::Text text;
    sf::Text score;

    if (!font.loadFromFile("SIXTY.TTF"))
    {
        std::cout << "Erreur de chargement de la police !" << std::endl;
    }

    std::string message{ "Ton score est de : " };
    message += std::to_string(membre);
    text.setFont(font);
    score.setFont(font);
    text.setString("GAME OVER");
    score.setString(message);
    text.setCharacterSize(40);
    score.setCharacterSize(24);
    text.setFillColor(sf::Color::Black);
    score.setFillColor(sf::Color::Black);
    text.setPosition(400, 250);
    score.setPosition(415, 320);

    window.draw(text);
    window.draw(score);
}
