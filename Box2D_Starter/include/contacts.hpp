//
// Created by Jerem on 05.11.2026.
//

#ifndef SFML_PROJECT_MASTER_CONTACTS_HPP
#define SFML_PROJECT_MASTER_CONTACTS_HPP
#include <box2d/box2d.h>

#include "sensor.hpp"

inline void SensorsContact(b2WorldId worldId) {

    const b2SensorEvents sensors = b2World_GetSensorEvents(worldId);


    for (int i = 0; i < sensors.beginCount; ++i) {
        const b2SensorBeginTouchEvent &e = sensors.beginEvents[i];


        auto *a = static_cast<Sensor *>(b2Shape_GetUserData(e.sensorShapeId));
        if (a) {
            a->Begin();
        }
    }


    for (int i = 0; i < sensors.endCount; ++i) {
        const b2SensorEndTouchEvent &e = sensors.endEvents[i];

        auto *a = static_cast<Sensor *>(b2Shape_GetUserData(e.sensorShapeId));
        if (a) {
            a->End();
        }
    }

}

#endif //SFML_PROJECT_MASTER_CONTACTS_HPP
