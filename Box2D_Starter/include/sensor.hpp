#ifndef SFML_PROJECT_MASTER_SENSOR_HPP
#define SFML_PROJECT_MASTER_SENSOR_HPP
#include <box2d/box2d.h>



class Sensor {
    b2BodyId body_ = b2_nullBodyId;
    int contacts_ = 0;              // combien de choses le touchent en ce moment


public:

    void Setup(b2BodyId body_id, b2Vec2 halfsize, b2Vec2 offset = {0.f, 0.f});
    bool haveTouch = false;

    void Begin() { ++contacts_; haveTouch = true; }
    void End() { if (contacts_ > 0) --contacts_; }
    bool Touching() const { return contacts_ > 0; }

};

#endif //SFML_PROJECT_MASTER_SENSOR_HPP
