cmake_minimum_required(VERSION 4.3)

# --- vcpkg (avant project(), c'est là qu'il lit ses réglages) ---
# Le vcpkg de CLion, avec MinGW : SFML et Box2D sont installés d'après vcpkg.json.
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{USERPROFILE}/.vcpkg-clion/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
set(VCPKG_TARGET_TRIPLET "x64-mingw-dynamic" CACHE STRING "")
set(VCPKG_HOST_TRIPLET "x64-mingw-dynamic" CACHE STRING "")

project(SFML_Project_Master)

set(CMAKE_CXX_STANDARD 23)

find_package(SFML COMPONENTS Audio Graphics Window System CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

# std::print / std::println : avec le MinGW de CLion (GCC 15), ils vivent dans une bibliothèque à part
if(MINGW)
    link_libraries(stdc++exp)
endif()

add_subdirectory(Starter)
add_subdirectory(Box2D_Starter)

#add_executable(Starter main.cpp src/game.cc)
#target_link_libraries(Starter PUBLIC SFML::Graphics)
