//
// Created by Jerem on 04.11.2

#include "Entity.hpp"
#include <SFML/Graphics/RenderStates.hpp>
#include"../include/constants.hpp"

void Entity::Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size) {
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);

    shape.setPosition(position);
    shape.setSize(size);
    shape.setOrigin(size / 2.f);
}

void Entity::SetUpPhysics(b2WorldId world, b2BodyType type, b2Vec2 position) {
    physics.Setup(world, type, position);
}
void Entity::Update(){

    physics.Update();

    constexpr float kPixelsParMetre = 50.f;
    sf::Vector2f newPosition;
    newPosition.x = physics.GetPosition().x * kPixelsParMetre;
    newPosition.y = physics.GetPosition().y * kPixelsParMetre;
    shape.setPosition (newPosition);
}
    void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        target.draw(shape, states);
    }

