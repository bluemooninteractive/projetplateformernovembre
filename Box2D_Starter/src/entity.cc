#include "../include/entity.hpp"
#include "../include/constants.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <print>

void Entity::Setup(sf::Color color, sf::Vector2f size) {
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);
    shape.setSize(size);
    shape.setOrigin({size.x / 2, size.y / 2});
}

void Entity::SetTexture(const sf::Texture &texture, bool repeter) {
    shape.setTexture(&texture);
    shape.setFillColor(sf::Color::White);   // blanc = les vraies couleurs de l'image
    shape.setOutlineThickness(0);           // plus de contour blanc
    if (repeter) {
        // La tuile se répète sur toute la taille (plateformes)
        shape.setTextureRect({{0, 0}, {static_cast<int>(shape.getSize().x),
                                       static_cast<int>(shape.getSize().y)}});
    }
    hasTexture = true;
}

void Entity::SetupPhysics(b2WorldId &world, b2BodyType type, b2Vec2 position, bool withSensor) {

    b2Vec2 halfSize = {Conversions::ScreenToPhysics(shape.getSize().x / 2), Conversions::ScreenToPhysics(shape.getSize().y / 2)};

    physics.Setup(
        world,
        type,
        position,
        halfSize
    );
    hasSensor = withSensor;
    if (hasSensor){
        grounded.Setup(physics.GetBodyId(), {halfSize.x * 0.8f, 0.08f}, {0.f, halfSize.y});
    }
}

void Entity::Update() {

    physics.Update();

    sf::Vector2f newPosition;
    newPosition.x = Conversions::PhysicsToScreen(physics.GetPosition().x);
    newPosition.y = Conversions::PhysicsToScreen(physics.GetPosition().y);

    if (hasSensor && !hasTexture) {   // le vert/rouge "au sol" teinterait le sprite   
        if (OnGround()){
            shape.setFillColor(sf::Color::Green);
        }else{
            shape.setFillColor(sf::Color::Red);
        }
    }
    shape.setPosition(newPosition);
}

// ----- les mouvements -----


void Entity::Right() {
    physics.SetXVelocity(walkSpeed);
}

void Entity::Left() {
    physics.SetXVelocity(-walkSpeed);
}

void Entity::Jump() {
    if (OnGround()) {            
        physics.Jump(jumpSpeed);
    }
}

void Entity::CancelMovement() {
    physics.SetXVelocity(0.f);          
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(shape, states);
}
