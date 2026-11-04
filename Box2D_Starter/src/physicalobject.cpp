//
// Created by Jerem on 04.11.2026
//

#include "physicalobject.h"

#include <print>

physicalobject::physicalobject(b2WorldId world) {
    def_ = b2DefaultBodyDef();
    def_.type = b2_dynamicBody;
    def_.position = {0.f, 0.f};

    body_ = b2CreateBody(world, &def_);

    b2Polygon square=b2MakeSquare(1.0f);

    b2ShapeDef shape_def_ = b2DefaultShapeDef();
    shape_def_.density = 1.0f;
    shape_def_.material.friction = 0.0f;
    b2CreatePolygonShape(body_, &shape_def_, &square);   // un carré est un polygone
}


void physicalobject::Update() {
    const b2Vec2 position = b2Body_GetPosition(body_);
    std::println("object position {} : {}", position.x, position.y);
}
