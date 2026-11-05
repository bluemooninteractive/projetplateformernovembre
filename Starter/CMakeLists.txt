add_executable(Starter main.cpp src/game.cc)   # pas le main.cc de Box2D_Starter : deux main() ne peuvent pas cohabiter

target_link_libraries(Starter PUBLIC SFML::Graphics SFML::Audio)