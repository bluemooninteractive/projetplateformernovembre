//
// Created by sebas on 04.11.2026.
//

#ifndef SFML_PROJECT_MASTER_ENTITY_HPP
#define SFML_PROJECT_MASTER_ENTITY_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "physical_object.hpp"
#include "sensor.hpp"

class Entity : public sf::Drawable {

    sf::RectangleShape shape;
    PhysicalObject physics;
    Sensor grounded;
    bool hasSensor = false;
    bool hasTexture = false;   // un sprite remplace la couleur unie
    float walkSpeed = 12.f;
    float jumpSpeed = 12.f;

    public:
    void Setup(sf::Color color, sf::Vector2f size);
    void SetTexture(const sf::Texture &texture, bool repeter = false);   // repeter : tuile répétée (plateformes)
    void SetupPhysics(b2WorldId &world, b2BodyType type, b2Vec2 position, bool withSensor = false);
    void Update();
    bool OnGround() const { return hasSensor && grounded.Touching(); }

    void Right();               // marche vers la droite
    void Left();                // marche vers la gauche
    void Jump();                // saute, seulement s'il touche le sol
    void Respawn(b2Vec2 position) { physics.Teleport(position); }   // en mètres
    sf::Vector2f GetScreenPosition() const { return shape.getPosition(); }   // en pixels (après Update)
    void CancelMovement();      // s'arrête à l'horizontale (garde sa chute ou son saut)
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

};

#endif //SFML_PROJECT_MASTER_ENTITY_HPP
