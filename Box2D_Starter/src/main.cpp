//
// Created by Jerem on 04.11.2026.
//

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <print>
#include <box2d/box2d.h>
#include <SFML/System.hpp>

#include "Entity.hpp"
#include "physicalobject.h"

int main() {

    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, 9.81f};

    b2WorldId monde = b2CreateWorld(&def);

    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Physics", sf::Style::Default);
    window.setFramerateLimit(240);

    constexpr float kPas = 1.f / 60.f;
    constexpr int kSousPas = 4;
    float accumulateur = 0.f;

    sf::Clock clock;
    double dt;

    Entity mario;
    mario.Setup(sf::Color::Red,{600.800})

    physicalobject falling;   // le carré qui tombe
    falling.Setup(monde, b2_dynamicBody, {0.f, 3.f});

    physicalobject sol;       // un second objet, immobile, sur lequel il va se poser
    sol.Setup(monde, b2_staticBody, {0.f, 10.f});

    while (window.isOpen()) {

        while (const std::optional evenement = window.pollEvent())
            if (evenement->is<sf::Event::Closed>())
                window.close();

        dt = clock.restart().asSeconds();
        accumulateur += dt;



        while (accumulateur >= kPas)   // autant de pas de physique que le temps écoulé en demande
        {
            b2World_Step(monde, kPas, kSousPas);
            falling.Update();   // affiche sa position
            accumulateur -= kPas;
        }

        window.clear(sf::Color::Magenta);
        window.display();
        window.draw(mario);
    }

    b2DestroyWorld(monde);
    return EXIT_SUCCESS;
}
