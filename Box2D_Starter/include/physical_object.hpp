#ifndef SFML_PROJECT_MASTER_OBJECT_HPP
#define SFML_PROJECT_MASTER_OBJECT_HPP
#include <box2d/types.h>

class PhysicalObject {
    b2BodyDef def_;
    b2BodyId body_;
    b2ShapeDef shape_def_;
    b2Vec2 halfSize_{};

public:
    void Setup(b2WorldId &world, b2BodyType type, b2Vec2 position, b2Vec2 halfSize);
    void Update();
    b2Vec2 GetPosition();
    b2BodyId GetBodyId() const { return body_; }   // pour y accrocher un capteur (Entity::grounded)

    void SetXVelocity(float xVelocity);   // la vitesse horizontale, en m/s (négative : vers la gauche)
    float GetXVelocity() const;           // la vitesse horizontale actuelle, en m/s
    void Jump(float speed);    // la vitesse de départ vers le haut, en m/s (Entity vérifie avant qu'il touche le sol)

};


#endif //SFML_PROJECT_MASTER_OBJECT_HPP
