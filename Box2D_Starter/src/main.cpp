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
    mario.Setup(sf::Color::Red,{600,400},{45,45});
    mario.SetUpPhysics(monde, b2_dynamicBody, {12.f, 2.f});   // son corps Box2D : 12 m = 600 px, 2 m = 100 px

    physicalobject falling;
    falling.Setup(monde, b2_dynamicBody, {0.f, 3.f});

    physicalobject sol;
    sol.Setup(monde, b2_staticBody, {0.f, 10.f});

    while (window.isOpen()) {

        while (const std::optional evenement = window.pollEvent())
            if (evenement->is<sf::Event::Closed>())
                window.close();

        dt = clock.restart().asSeconds();
        accumulateur += dt;



        while (accumulateur >= kPas)
        {
            b2World_Step(monde, kPas, kSousPas);
            mario.Update();
            falling.Update();
            sol.Update();
            accumulateur -= kPas;
        }

        window.clear(sf::Color::Black);
        window.draw(mario);
        window.display();
    }

    b2DestroyWorld(monde);
    return EXIT_SUCCESS;
}
