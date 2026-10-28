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

# --- SFML (installé par vcpkg d'après vcpkg.json) ---
find_package(SFML 3 COMPONENTS Graphics Window Audio System REQUIRED)

# --- Le jeu ---
# Chaque nouveau .cc se rajoute ici.
add_executable(SFML_Starter
        Starter/src/main.cc
        Starter/src/game.cc)

target_include_directories(SFML_Starter PRIVATE Starter/include)   # les .hpp
target_link_libraries(SFML_Starter PRIVATE SFML::Graphics SFML::Window SFML::Audio SFML::System)

# --- Les ressources ---
# Le .exe tourne dans cmake-build-debug : on y recopie les images à chaque compilation.
add_custom_command(TARGET SFML_Starter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/Starter/Ressources"
        "$<TARGET_FILE_DIR:SFML_Starter>/Ressources")
