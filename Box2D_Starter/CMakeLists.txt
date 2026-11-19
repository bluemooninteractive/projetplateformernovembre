add_executable(Box2D_Starter main.cc
        include/physical_object.hpp
        src/physical_object.cc
        include/entity.hpp
        src/entity.cc
        include/constants.hpp
        include/sensor.hpp
        src/sensor.cpp
        include/contacts.hpp
        include/geme.hpp
        src/geme.cpp
        include/arrivee.hpp
        include/settings.hpp)

target_link_libraries(Box2D_Starter PUBLIC SFML::Graphics SFML::Audio box2d::box2d)

# Dossier des images (le .exe tourne dans cmake-build-debug : on donne le chemin complet)
target_compile_definitions(Box2D_Starter PRIVATE
        ASSETS_DIR="${CMAKE_SOURCE_DIR}/Starter/ressources/kenney_desert-shooter-pack_1.0/PNG/"
        PIXEL_DIR="${CMAKE_SOURCE_DIR}/Starter/ressources/kenney_pixel-platformer/Tiles/")
