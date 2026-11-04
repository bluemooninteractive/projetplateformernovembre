//
// Created by Jerem on 04.11.2026.
//

#include <cstdio>

int main() {

    b2WorldDef def = b2DefaultWorldDef();
    def.gravity = {0.f, -9.81f};          // vers le bas, en m/s²

    b2WorldId monde = b2CreateWorld(&def);

    constexpr float kPas = 1.f / 60.f;
    constexpr int kSousPas = 4;
    float accumulateur += 0.0f;
  sf::Clock clock;
    float dt;

    while (true)

    dt= clock.restart().asSeconds();
    accumulateur += dt;
    while (accumulateur > kPas)
    {
        std::printf("time accumulateur: {}", accumulateur);
        b2World_step(monde, kSousPas);
        accumulateur -= kPas;

    }












}
