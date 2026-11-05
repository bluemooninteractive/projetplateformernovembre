//
// Created by Jerem on 05.11.2026.
//
#include <Box2D/Box2D.h>

void sensor::Setup(b2World* world,b2Vec2 position,b2Vec2 halfsize) {
    bodyDef=b2BodyDef();
    bodyDef_.type=b2_staticBody;
    bodyDef_.position=position;
    body_=b2CreateBody(world,bodyDef_);

    const b2Polygon pieds = b2MakeBox(halfsize.x,halfsize.y);

    b2ShapeDef def = b2DefaultBodyDef()
    def.isSensor = true;
    def.enableSensorEvents=true;
    def.userData = & body_;

    b2CreatePolygonShape(body_,&def,&pieds);


    void sensor::Update() {
        const b2SensorBeginTouchEvent  &e =sensors.beginEvents [i];

        auto *a = static_cast<Objet *>(b2Shape_GetUserData(e.shapeidA));
        auto *b = static_cast<Objet *>(b2Shape_GetUserData(e.shapeidB));

        if (a&& b) {
            a->Touche(*b);
            b->Touche(*a);
        }
    }
}