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
    // y descend (gravité +9.81) : les pieds sont en +halfSize_.y. Un peu moins large que le corps,
    // pour ne pas prendre un mur touché de côté pour un sol.
    const b2Polygon feet = b2MakeOffsetBox(halfSize_.x * 0.8f, 0.08f, {0.f, halfSize_.y}, b2Rot_identity);

    b2ShapeDef def = b2DefaultShapeDef();
    def.isSensor = true;                // il détecte, il n'arrête rien
    def.enableSensorEvents = true;      // sans ça : aucun événement
    def.userData = &groundContacts_;    // l'événement saura quel compteur changer

    b2CreatePolygonShape(body_, &def, &feet);
}

void PhysicalObject::ProcessSensorEvents(b2WorldId world) {
    const b2SensorEvents events = b2World_GetSensorEvents(world);

    for (int i = 0; i < events.beginCount; ++i) {
        int* counter = static_cast<int*>(b2Shape_GetUserData(events.beginEvents[i].sensorShapeId));
        if (counter) ++*counter;        // un sol de plus sous les pieds
    }
    for (int i = 0; i < events.endCount; ++i) {
        int* counter = static_cast<int*>(b2Shape_GetUserData(events.endEvents[i].sensorShapeId));
        if (counter) --*counter;        // un sol de moins
    }
}
