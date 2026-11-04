//
// Created by Jerem on 04.11.2026.
//

#ifndef SFML_STARTER_OBJECT_H
#define SFML_STARTER_OBJECT_H
#include <box2d/box2d.h>

class physicalobject {
    b2BodyDef def_;
    b2BodyId body_;
    b2ShapeDef shape_def_;

public:
    // crée le corps dans le monde : son type (dynamique, statique...) et sa position de départ, en mètres
    void Setup(b2WorldId world, b2BodyType type, b2Vec2 position);
    void Update();
};

#endif
