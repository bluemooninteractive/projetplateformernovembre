cmake_minimum_required(VERSION 3.28)

# --- vcpkg (avant project(), c'est là qu'il lit ses réglages) ---
# Le vcpkg de CLion, pour que le projet marche où qu'il soit, sans option dans CLion.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
# CLion compile avec MinGW : SFML doit être préparé pour MinGW, pas pour Visual Studio.
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "")
set(VCPKG_HOST_TRIPLET "x64-mingw-dynamic" CACHE STRING "")

project(SFML_Starter CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- SFML et Box2D (installés par vcpkg d'après vcpkg.json) ---
find_package(SFML 3 COMPONENTS Graphics Window Audio System REQUIRED)
find_package(box2d CONFIG REQUIRED)

# --- Le starter ---
add_executable(SFML_Starter
        Starter/src/main.cc
        Starter/src/game.cc)

target_include_directories(SFML_Starter PRIVATE Starter/include)
target_link_libraries(SFML_Starter PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)

# --- La page Box2D : un programme à part (chaque exécutable a son propre main) ---
add_executable(Box2D_Starter
        Box2D_Starter/src/main.cpp
        Box2D_Starter/src/physicalobject.cpp)
target_include_directories(Box2D_Starter PRIVATE Box2D_Starter/include)   # les .h
target_link_libraries(Box2D_Starter PRIVATE SFML::Graphics SFML::Window SFML::System box2d::box2d)
# std::print / std::println : avec le MinGW de CLion (GCC 15), ils vivent dans une bibliothèque à part
if(MINGW)
    target_link_libraries(Box2D_Starter PRIVATE stdc++exp)
endif()
