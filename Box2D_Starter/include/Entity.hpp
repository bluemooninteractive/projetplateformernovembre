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
        // la signature exacte de sf::Drawable : sinon window.draw(...) n'appelle pas notre fonction
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;






};







#endif //SFML_STARTER_ENTITY_HPP
