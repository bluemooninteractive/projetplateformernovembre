//
// Created by Jerem on 04.11.2026
//

#include "physicalobject.h"

#include <print>

void physicalobject::Setup(b2WorldId world, b2BodyType type, b2Vec2 position) {
    def_ = b2DefaultBodyDef();
    def_.type = type;
    def_.position = position;

    body_ = b2CreateBody(world, &def_);

    b2Polygon square=b2MakeSquare(0.5f);

    b2ShapeDef shape_def_ = b2DefaultShapeDef();
    shape_def_.density = 1.0f;
    shape_def_.material.friction = 0.0f;
    shape_def_.material.restitution = 1.0f;
    b2CreatePolygonShape(body_, &shape_def_, &square);

    b2MassData myMassData{};
    myMassData.mass = 5.0f;
    myMassData.center = {0.0f, 0.0f};
    myMassData.rotationalInertia = 100.0f;
    b2Body_SetMassData(body_, myMassData);
}


void physicalobject::Update() {
    const b2Vec2 position = b2Body_GetPosition(body_);
    std::println("object position {} : {}", b2Body_GetPosition(body_).x, b2Body_GetPosition(body_).y);
}

b2Vec2 physicalobject::GetPosition(){
    return b2Body_GetPosition(body_);
}