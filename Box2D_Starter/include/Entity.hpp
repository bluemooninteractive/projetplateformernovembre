//
// Created by Jerem on 04.11.2026.
//

#ifndef SFML_STARTER_ENTITY_HPP
#define SFML_STARTER_ENTITY_HPP
#include "physicalobject.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

class Entity : public sf::Drawable {

    sf::RectangleShape shape;
    sf::Texture texture;

 physicalobject physics;



    public:
    void Update();
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size);
    void SetUpPhysics(b2WorldId world, b2BodyType type, b2Vec2 position);   // crée son corps Box2D






};







#endif //SFML_STARTER_ENTITY_HPP
