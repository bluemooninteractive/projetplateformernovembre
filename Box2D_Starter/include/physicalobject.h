//
// Created by Jerem on 04.11.2026.
//

#ifndef SFML_STARTER_OBJECT_H
#define SFML_STARTER_OBJECT_H
#include <box2d/box2d.h>

class physicalobject {
    b2BodyId body_ = b2_nullBodyId;

public:
    b2Vec2 GetPosition() const;


    void Setup(b2WorldId world, b2BodyType type, b2Vec2 position, b2Vec2 size);
    void Update();
};

#endif
