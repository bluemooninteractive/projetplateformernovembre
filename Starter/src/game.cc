#include "game.hpp"
#include <cmath>
#include <optional>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Joystick.hpp>


void Game::initialize()
{
    window.create(sf::VideoMode({1920, 1080}), "The Game", sf::Style::Default);
    window.setFramerateLimit(120);

    if (!texture.loadFromFile("Ressources/character_maleAdventurer_attack0.png"))
        return;

    player.emplace(texture);
    player->setOrigin(player->getLocalBounds().getCenter());
    player->setPosition(sf::Vector2f(window.getSize()) / 2.f);
}

void Game::loop()
{
    initialize();
    while (window.isOpen())
    {
        processEvents();
        sf::Joystick::update();

        if (player && sf::Joystick::isConnected(0))
        {
            const float stick = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X);
            const float croix = sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX);
            float x;
            if (std::abs(stick) >= 15.f)   // stick poussé (au-delà de la zone morte)
                x = stick;
            else if (croix != 0.f)         // sinon, la croix directionnelle
                x = croix;
            else                           // rien de touché
                x = 0.f;
            const float vitesse = 8.f;
            player->move({x / 100.f * vitesse, 0.f});
        }

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

void Game::render()
{
    window.clear(sf::Color::Black);
    if (player)
        window.draw(*player);
    window.display();
}
