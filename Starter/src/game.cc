#include "game.hpp"

#include <optional>

#include <SFML/Window/Event.hpp>


Game::Game()
    : window(sf::VideoMode({1920, 1080}), "The Game", sf::Style::Default),
      cupheadTexture("Ressources/Cuphead_Run_03.png")
{
    window.setFramerateLimit(120);
    cuphead = std::make_unique<sf::Sprite>(cupheadTexture);
    cuphead->setOrigin(cuphead->getLocalBounds().getCenter());
    cuphead->setPosition(sf::Vector2f(window.getSize()) / 2.f);
}

void Game::loop()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();
        else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            if (key->scancode == sf::Keyboard::Scancode::Escape)
                window.close();
    }
}

void Game::update()
{
}

void Game::render()
{
    window.clear(sf::Color::Black);
    window.draw(*cuphead);
    window.display();
}
