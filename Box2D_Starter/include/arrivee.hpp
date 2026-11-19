//
// Created by Jerem on 19.11.2026.
//

#ifndef SFML_PROJECT_MASTER_ARRIVEE_HPP
#define SFML_PROJECT_MASTER_ARRIVEE_HPP
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.hpp"
#include "sensor.hpp"

class Arrivee : public sf::Drawable {
    sf::RectangleShape mat_;
    sf::RectangleShape drapeau_;
    Sensor sensor_;

public:
    void Setup(b2WorldId world, sf::Vector2f pos) {
        const sf::Vector2f taille = {6.f, 60.f};            // le mât
        mat_.setSize(taille);
        mat_.setOrigin({taille.x / 2.f, taille.y});           // origine = le pied
        mat_.setPosition(pos);
        mat_.setFillColor(sf::Color::White);

        drapeau_.setSize({30.f, 20.f});
        drapeau_.setPosition({pos.x + 3.f, pos.y - taille.y}); // en haut du mât
        drapeau_.setFillColor(sf::Color::Green);

        // Capteur : un peu plus large que le mât, mais qui s'arrête 5 px
        // AU-DESSUS du sol, sinon il "touche" la plateforme et l'arrivée
        // est atteinte dès le départ.
        const float marge = 5.f;
        b2BodyDef def = b2DefaultBodyDef();
        def.type = b2_staticBody;
        def.position = {Conversions::ScreenToPhysics(pos.x),
                        Conversions::ScreenToPhysics(pos.y - marge - (taille.y - marge) / 2.f)};
        b2BodyId body = b2CreateBody(world, &def);
        sensor_.Setup(body, {Conversions::ScreenToPhysics(15.f),
                             Conversions::ScreenToPhysics((taille.y - marge) / 2.f)});
    }

    // Sprite du drapeau (pack Pixel Platformer) à la place du mât + rectangle vert.
    // Le capteur ne change pas. La texture doit vivre aussi longtemps que l'arrivée.
    void SetTexture(const sf::Texture &texture) {
        const sf::Vector2f pied = mat_.getPosition();   // le pied du mât, posé sur la plateforme
        mat_.setSize({0.f, 0.f});                       // plus de mât dessiné (il est dans l'image)
        drapeau_.setSize({40.f, 40.f});
        drapeau_.setPosition({pied.x - 12.f, pied.y - 40.f});   // le bas de l'image sur la plateforme
        drapeau_.setTexture(&texture);
        drapeau_.setFillColor(sf::Color::White);
    }

    bool Atteinte() const { return sensor_.Touching(); }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(mat_, states);
        target.draw(drapeau_, states);
    }
};

#endif //SFML_PROJECT_MASTER_ARRIVEE_HPP

