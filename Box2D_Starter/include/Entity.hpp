//
// Created by Jerem on 04.11.2026.
//

#ifndef SFML_STARTER_ENTITY_HPP
#define SFML_STARTER_ENTITY_HPP
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>

class Entity : public sf::Drawable {

    sf::RectangleShape shape;
    sf::Texture texture;


    public:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void Setup(sf::Color color, sf::Vector2f position, sf::Vector2f size);






};







#endif //SFML_STARTER_ENTITY_HPP
