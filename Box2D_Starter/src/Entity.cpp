//
// Created by Jerem on 04.11.2

#include "Entity.hpp"
#include <SFML/Graphics/RenderStates.hpp>

void Entity::Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size) {
    shape.setFillColor(color);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(1);

    shape.setPosition(position)

    shape.setSize(size)


}
{
    target.draw(shape, states);
}
