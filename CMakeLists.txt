cmake_minimum_required(VERSION 3.28)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "")
set(VCPKG_HOST_TRIPLET "x64-mingw-dynamic" CACHE STRING "")

project(SFML_Starter CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window Audio System REQUIRED)
find_package(box2d CONFIG REQUIRED)

add_executable(SFML_Starter
        Starter/src/main.cc
        Starter/src/game.cc)

target_include_directories(SFML_Starter PRIVATE Starter/include)
target_link_libraries(SFML_Starter PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)

add_executable(Box2D_Starter
        Box2D_Starter/src/main.cpp
        Box2D_Starter/src/physicalobject.cpp
        Box2D_Starter/include/Entity.hpp
        Box2D_Starter/src/Entity.cpp
        Box2D_Starter/include/constants.hpp
)
target_include_directories(Box2D_Starter PRIVATE Box2D_Starter/include)   # les .h
target_link_libraries(Box2D_Starter PRIVATE SFML::Graphics SFML::Window SFML::System box2d::box2d)
if(MINGW)
    target_link_libraries(Box2D_Starter PRIVATE stdc++exp)
endif()
