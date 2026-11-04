//
// Created by Jerem on 04.11.2026.
//

#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <print>
#include <box2d/box2d.h>
#include <SFML/System.hpp>

#include "physicalobject.h"

int main() {

    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, 9.81f};

    b2WorldId monde = b2CreateWorld(&def);
    physicalobject carre(monde);   // un carré de 1 m, qui tombe
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Physics", sf::Style::Default);
    window.setFramerateLimit(240);

    constexpr float kPas = 1.f / 60.f;
    constexpr int kSousPas = 4;
    float accumulateur = 0.f;

    sf::Clock clock;
    float dt;

    while (window.isOpen()) {

        while (const std::optional evenement = window.pollEvent())
            if (evenement->is<sf::Event::Closed>())
                window.close();

        dt = clock.restart().asSeconds();
        accumulateur += dt;
        while (accumulateur >= kPas)
        {
            b2World_Step(monde, kPas, kSousPas);
            carre.Update();   // affiche sa position
            accumulateur -= kPas;
        }

        window.clear(sf::Color::Magenta);
        window.display();
    }

    b2DestroyWorld(monde);
    return EXIT_SUCCESS;
}
