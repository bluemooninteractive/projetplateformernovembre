cmake_minimum_required(VERSION 3.28)


project(SFML_Starter CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SFML 3 COMPONENTS Graphics Window Audio System REQUIRED)


add_executable(SFML_Starter
        Starter/src/main.cc
        Starter/src/game.cc
        Box2D_Starter/main.cpp)

target_include_directories(SFML_Starter PRIVATE Starter/include)
target_link_libraries(SFML_Starter PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)


