//
// Created by Jerem on 04.11.2026
//

#include "physicalobject.h"

#include <print>

void physicalobject::Setup(b2WorldId world, b2BodyType type, b2Vec2 position, b2Vec2 size) {
    b2BodyDef def = b2DefaultBodyDef();
    def.type = type;
    def.position = position;

    body_ = b2CreateBody(world, &def);

    b2Polygon box = b2MakeBox(size.x / 2.f, size.y / 2.f);

    b2ShapeDef shape_def = b2DefaultShapeDef();
    shape_def.density = 1.0f;
    shape_def.material.friction = 0.0f;
    shape_def.material.restitution = 1.0f;
    b2CreatePolygonShape(body_, &shape_def, &box);

    b2MassData myMassData{};
    myMassData.mass = 5.0f;
    myMassData.center = {0.0f, 0.0f};
    myMassData.rotationalInertia = 100.0f;
    b2Body_SetMassData(body_, myMassData);
}


void physicalobject::Update() {
    const b2Vec2 position = b2Body_GetPosition(body_);
    std::println("object position {} : {}", position.x, position.y);
}

b2Vec2 physicalobject::GetPosition() const {
    return b2Body_GetPosition(body_);
}
