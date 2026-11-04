//
// Created by Jerem on 04.11.2026.
//

#ifndef SFML_STARTER_CONSTANTS_HPP
#define SFML_STARTER_CONSTANTS_HPP



namespace Conversion {
    constexpr float pixelToMeters = 0.05f;   // 1 pixel = 0,05 m, donc 20 pixels par mètre

    constexpr float PhysicsToScreen(float meters) {
        return meters / pixelToMeters;
    }

    constexpr float ScreenToPhysics(float pixels) {
        return pixels * pixelToMeters;
    }
}




#endif //SFML_STARTER_CONSTANTS_HPP
