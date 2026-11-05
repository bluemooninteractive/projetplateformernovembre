//
// Created by Jerem on 05.11.2026.
//
#include "../include/sensor.hpp"


void Sensor::Setup(b2BodyId body_id, b2Vec2 halfsize, b2Vec2 offset) {
    body_ = body_id;

    const b2Polygon box = b2MakeOffsetBox(halfsize.x, halfsize.y, offset, b2Rot_identity);

    b2ShapeDef def = b2DefaultShapeDef();
    def.isSensor = true;              // il détecte, il n'arrête rien
    def.enableSensorEvents = true;    // sans ça : aucun événement
    def.userData = this;              // SensorsContact retrouvera ce Sensor

    b2CreatePolygonShape(body_, &def, &box);
}
