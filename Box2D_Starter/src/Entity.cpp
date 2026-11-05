//
// Created by Jerem on 04.11.2026.
//

#include "Entity.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include "constants.hpp"

void Entity::Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size) {
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);

    shape.setPosition(position);
    shape.setSize(size);
    shape.setOrigin(size / 2.f);
}

void Entity::SetUpPhysics(b2WorldId world, b2BodyType type) {
    const sf::Vector2f pos = shape.getPosition();
    const sf::Vector2f size = shape.getSize();
    physics.Setup(world, type,
                  {Conversion::ScreenToPhysics(pos.x), Conversion::ScreenToPhysics(pos.y)},
                  {Conversion::ScreenToPhysics(size.x), Conversion::ScreenToPhysics(size.y)});
}

void Entity::Update() {
    physics.Update();

    const b2Vec2 p = physics.GetPosition();
    shape.setPosition({Conversion::PhysicsToScreen(p.x), Conversion::PhysicsToScreen(p.y)});
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}
