//
// Created by Jerem on 19.11.2026.
//

#ifndef SFML_PROJECT_MASTER_GEME_HPP
#define SFML_PROJECT_MASTER_GEME_HPP
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>
#include "constants.hpp"
#include "sensor.hpp"

class Geme : public sf::Drawable {
    sf::RectangleShape shape_;
    Sensor sensor_;
    bool collected_ = false;

public:
    void Setup(b2WorldId world, sf::Vector2f pos, sf::Vector2f size) {
        shape_.setSize(size);
        shape_.setOrigin(size / 2.f);
        shape_.setPosition(pos);
        shape_.setFillColor(sf::Color::Cyan);

        b2BodyDef def = b2DefaultBodyDef();
        def.type = b2_staticBody;
        def.position = {Conversions::ScreenToPhysics(pos.x),
                        Conversions::ScreenToPhysics(pos.y)};
        b2BodyId body = b2CreateBody(world, &def);

        sensor_.Setup(body, {Conversions::ScreenToPhysics(size.x / 2.f),
                             Conversions::ScreenToPhysics(size.y / 2.f)});
    }

    bool TryCollect() {
        if (!collected_ && sensor_.Touching()) {
            collected_ = true;
            return true;
        }
        return false;
    }

    void SetTexture(const sf::Texture &texture) {
        shape_.setTexture(&texture);
        shape_.setFillColor(sf::Color::White);  
    }

    void Reset() { collected_ = false; }   // de nouveau à ramasser

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        if (!collected_) target.draw(shape_, states);
    }
};
#endif //SFML_PROJECT_MASTER_GEME_HPP


