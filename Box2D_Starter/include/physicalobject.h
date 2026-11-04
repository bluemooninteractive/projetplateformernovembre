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
    explicit physicalobject(b2WorldId monde);
    void Update();
};

#endif
