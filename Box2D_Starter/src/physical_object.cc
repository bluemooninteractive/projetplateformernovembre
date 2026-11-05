#include "../include/physical_object.hpp"

#include <print>
#include <box2d/box2d.h>

void PhysicalObject::Setup(b2WorldId &world, b2BodyType type, b2Vec2 position, b2Vec2 halfSize) {

    def_ = b2DefaultBodyDef();
    def_.type = type;
    def_.position = position;

    body_ = b2CreateBody(world, &def_);
    halfSize_ = halfSize;

    b2Polygon square = b2MakeBox(halfSize.x, halfSize.y);

    shape_def_ = b2DefaultShapeDef();
    shape_def_.density = 1.0f;
    shape_def_.material.friction = 0.0f;
    shape_def_.material.restitution = 0.0f;
    shape_def_.enableSensorEvents = true;   // pour que les capteurs la voient (faux par défaut depuis Box2D 3.1)
    b2CreatePolygonShape(body_, &shape_def_, &square);

    b2MassData myMassData;
    myMassData.mass = 5.0f;
    myMassData.center = {0.0f, 0.0f};
    myMassData.rotationalInertia = 0.0f;
    b2Body_SetMassData(body_, myMassData);

}

void PhysicalObject::Update() {
    std::println("object position , {} : {}", b2Body_GetPosition(body_).x, b2Body_GetPosition(body_).y);
}

b2Vec2 PhysicalObject::GetPosition() {
    return b2Body_GetPosition(body_);
}

void PhysicalObject::AddGroundSensor() {
    // y descend : les pieds sont en +halfSize_.y ; un peu moins large que le corps, pour ignorer les murs
    groundSensor_.Setup(body_, {halfSize_.x * 0.8f, 0.08f}, {0.f, halfSize_.y});
}

// On passe par le corps Box2D (sa vitesse) : c'est lui qui décide où est l'objet, l'image suit dans Entity::Update.
void PhysicalObject::Move(float speedX) {
    b2Vec2 v = b2Body_GetLinearVelocity(body_);
    v.x = speedX;                                  // on garde la vitesse verticale (chute, saut)
    b2Body_SetLinearVelocity(body_, v);
}

void PhysicalObject::Jump(float speed) {
    if (!OnGround()) return;                       // pas de saut en l'air
    b2Vec2 v = b2Body_GetLinearVelocity(body_);
    v.y = -speed;                                  // y descend : vers le haut, c'est négatif
    b2Body_SetLinearVelocity(body_, v);
}
