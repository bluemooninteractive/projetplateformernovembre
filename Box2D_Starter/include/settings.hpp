//
// Created by Jerem on 19.11.2026.
//

#ifndef SFML_PROJECT_MASTER_SETTINGS_HPP
#define SFML_PROJECT_MASTER_SETTINGS_HPP

#include <SFML/System/Vector2.hpp>
#include <box2d/box2d.h>

namespace Settings {

   constexpr float kGravite = 16.f;
   constexpr float kPas = 1.f / 60.f;
   constexpr int kSousPas = 4;


   constexpr unsigned kFenetreLargeur = 1200;
   constexpr unsigned kFenetreHauteur = 800;
   constexpr sf::Vector2f kCamera = {720.f, 480.f};

   constexpr sf::Vector2f kTailleJoueur = {30.f, 30.f};
   constexpr float kVitesseMarche = 12.f;
   constexpr float kVitesseSaut = 12.f;
   constexpr float kMemoireSaut = 0.15f;
   constexpr b2Vec2 kDepart = {1.f, 1.f};

   constexpr int kEssaisMax = 5;

}

#endif //SFML_PROJECT_MASTER_SETTINGS_HPP
