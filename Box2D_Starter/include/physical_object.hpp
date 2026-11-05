#ifndef SFML_PROJECT_MASTER_OBJECT_HPP
#define SFML_PROJECT_MASTER_OBJECT_HPP
#include <box2d/types.h>

class PhysicalObject {
    b2BodyDef def_;
    b2BodyId body_;
    b2ShapeDef shape_def_;
    b2Vec2 halfSize_{};

    // le capteur de sol : le nombre de sols touchés par les pieds (un compteur, pas un booléen :
    // on peut toucher deux plateformes à la fois). Son adresse est donnée à Box2D : l'objet ne doit pas bouger en mémoire.
    int groundContacts_ = 0;

public:
    void Setup(b2WorldId &world, b2BodyType type, b2Vec2 position, b2Vec2 halfSize);
    void Update();
    b2Vec2 GetPosition();

    void AddGroundSensor();                           // une fine bande sous les pieds, qui détecte sans arrêter
    bool OnGround() const { return groundContacts_ > 0; }
    static void ProcessSensorEvents(b2WorldId world); // à appeler après chaque b2World_Step

};


#endif //SFML_PROJECT_MASTER_OBJECT_HPP
