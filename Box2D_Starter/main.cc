#include <algorithm>
#include <cstdlib>
#include <format>
#include <print>
#include <box2d/box2d.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "include/constants.hpp"
#include "include/entity.hpp"
#include "include/physical_object.hpp"
#include "include/contacts.hpp"
#include "include/geme.hpp"
#include "include/arrivee.hpp"
#include <vector>

int main() {
   b2WorldDef def = b2DefaultWorldDef();
   def.gravity = {0.f, 16.f};

   b2WorldId monde = b2CreateWorld(&def);

   sf::RenderWindow window(sf::VideoMode({1200, 800}), "Physics", sf::Style::Default);
   window.setFramerateLimit(240);
   window.setKeyRepeatEnabled(false);   // un appui = un seul KeyPressed, donc un seul saut

   constexpr float kPas = 1.f / 60.f;
   constexpr int kSousPas = 4;
   float accumulateur_ = 0.f;

   sf::Clock clock;

   Entity mario;
   mario.Setup(sf::Color::Red, {30,30});
   const b2Vec2 departMario = {1, 1};   // en mètres : là où Mario (ré)apparaît
   mario.SetupPhysics(monde, b2_dynamicBody, departMario, true);
   bool marioAuSol = false;

   // Le sol en 3 morceaux, avec 2 trous de 120 px (tomber = un essai en moins)
   struct MorceauSol { float x, largeur; };   // x = le CENTRE, en pixels
   const MorceauSol morceauxSol[] = {
      { 200.f, 400.f},   // A : x 0 à 400 (le départ de Mario est dessus)
      { 660.f, 280.f},   // B : x 520 à 800
      {1060.f, 280.f},   // C : x 920 à 1200
   };
   std::vector<Entity> sol(std::size(morceauxSol));   // taille fixée AVANT Setup
   for (std::size_t i = 0; i < sol.size(); ++i) {
      sol[i].Setup(sf::Color::Yellow, {morceauxSol[i].largeur, 18.f});   // 18 px = une tuile du pack
      sol[i].SetupPhysics(monde, b2_staticBody,
         {Conversions::ScreenToPhysics(morceauxSol[i].x), Conversions::ScreenToPhysics(779.f)});   // centre : le dessus reste à y = 770
   }

   // Parcours de 7 plateformes (+ le sol = 8 en tout), en pixels.
   // Le saut monte d'environ 90 px (vitesse 12 m/s, gravite 16) :
   // chaque marche monte de 70 px pour rester atteignable.
   struct Plateforme { float x, y, largeur; };   // x, y = le CENTRE
   const Plateforme parcours[] = {
      { 250.f, 710.f, 180.f},   // 1 : premiere marche depuis le sol
      { 500.f, 640.f, 160.f},   // 2
      { 760.f, 570.f, 160.f},   // 3
      {1020.f, 500.f, 180.f},   // 4 : a droite
      { 780.f, 430.f, 140.f},   // 5 : on repart vers la gauche
      { 520.f, 360.f, 160.f},   // 6
      { 240.f, 290.f, 200.f},   // 7 : le sommet
   };
   std::vector<Entity> plateformes(std::size(parcours));   // taille fixee AVANT Setup
   for (std::size_t i = 0; i < plateformes.size(); ++i) {
      plateformes[i].Setup(sf::Color::White, {parcours[i].largeur, 18.f});   // 18 px = une tuile du pack
      plateformes[i].SetupPhysics(monde, b2_staticBody,
         {Conversions::ScreenToPhysics(parcours[i].x), Conversions::ScreenToPhysics(parcours[i].y - 1.f)});   // -1 : le dessus ne bouge pas
   }

   // Gemmes à ramasser (positions et taille en pixels)
   std::vector<Geme> gemmes(3);   // taille fixée AVANT Setup (le capteur garde l'adresse)
   gemmes[0].Setup(monde, { 500.f, 605.f}, {20.f, 20.f});   // sur la plateforme 2
   gemmes[1].Setup(monde, {1020.f, 465.f}, {20.f, 20.f});   // sur la plateforme 4
   gemmes[2].Setup(monde, { 240.f, 255.f}, {20.f, 20.f});   // au sommet (7)
   int score = 0;

   // Sprite des gemmes (pack Kenney du projet, licence CC0)
   sf::Texture texGemme;
   if (!texGemme.loadFromFile(PIXEL_DIR "tile_0067.png")) {   // diamant bleu
      std::println("Image de gemme introuvable : verifie PIXEL_DIR dans Box2D_Starter/CMakeLists.txt");
      return EXIT_FAILURE;
   }
   for (auto &g : gemmes) g.SetTexture(texGemme);

   // Sprites de Mario et des plateformes (pack Kenney, CC0)
   sf::Texture texMario, texBrique;
   if (!texMario.loadFromFile(PIXEL_DIR "Characters/tile_0000.png") ||   // alien vert
       !texBrique.loadFromFile(PIXEL_DIR "tile_0002.png")) {   // herbe sur terre
      std::println("Images introuvables : verifie ASSETS_DIR");
      return EXIT_FAILURE;
   }
   texBrique.setRepeated(true);              // la brique se répète sur toute la plateforme
   mario.SetTexture(texMario);
   for (auto &m : sol) m.SetTexture(texBrique, true);   // le sol
   for (auto &p : plateformes) p.SetTexture(texBrique, true);

   Arrivee arrivee;
   arrivee.Setup(monde, {160.f, 280.f});   // pied du mât posé sur le sommet
   sf::Texture texDrapeau;
   if (!texDrapeau.loadFromFile(PIXEL_DIR "tile_0111.png")) {   // drapeau rouge
      std::println("Image du drapeau introuvable : verifie PIXEL_DIR");
      return EXIT_FAILURE;
   }
   arrivee.SetTexture(texDrapeau);
   bool gagne = false;

   // Essais : Mario en perd un quand il tombe hors de l'écran
   constexpr int kEssaisMax = 5;
   int essais = kEssaisMax;
   bool gameOver = false;
   auto majTitre = [&] {
      window.setTitle(gagne
         ? std::format("BRAVO ! Arrivee atteinte - score {} - R pour rejouer", score)
         : gameOver
         ? std::format("GAME OVER - score {} - R pour rejouer", score)
         : std::format("Physics - essais : {} / {} - score : {}", essais, kEssaisMax, score));
   };
   majTitre();

   // Caméra : on montre une zone plus petite que le niveau, donc tout paraît plus gros.
   // 720 x 480 = 60 % du niveau (1200 x 800) -> zoom x1,67. Garder le rapport 3:2.
   sf::View camera({0.f, 0.f}, {720.f, 480.f});

   float sautEnAttente = 0.f;   // > 0 : un appui sur Espace attend que Mario touche le sol

   while (window.isOpen()) {

      const float dt = std::min(clock.restart().asSeconds(), 0.25f);   // plafonné après un gel de la fenêtre
      accumulateur_ += dt;

      while (const std::optional event = window.pollEvent()) {
         if (event->is<sf::Event::Closed>()) {
            window.close();
         }


         if (const auto* touche = event->getIf<sf::Event::KeyPressed>()) {
            if (touche->code == sf::Keyboard::Key::Space && !(gameOver || gagne)) {
               sautEnAttente = 0.15f;   // on retient l'appui 0,15 s (appui un peu trop tôt = saut quand même)
            }
            // Game over : R = on recommence tout
            // R : on recommence la partie (à tout moment)
            if (touche->code == sf::Keyboard::Key::R) {
               essais = kEssaisMax;
               score = 0;
               gameOver = false;
               gagne = false;
               for (auto &g : gemmes) g.Reset();
               mario.Respawn(departMario);
               majTitre();
               std::println("Nouvelle partie !");
            }
         }
      }

      if (gameOver || gagne)
         mario.CancelMovement();   // plus de contrôle tant qu'on n'a pas relancé
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
         mario.Left();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
         mario.Right();
      else
         mario.CancelMovement();

      while (accumulateur_ >= kPas)
      {
         b2World_Step(monde, kPas, kSousPas);
         SensorsContact(monde);

         // Arrivée : testée juste après la physique (capteurs à jour)
         if (!gagne && !gameOver && arrivee.Atteinte()) {
            gagne = true;
            std::println("BRAVO ! Arrivee atteinte avec {} gemme(s) et {} essai(s) restants.", score, essais);
            majTitre();
         }

         accumulateur_ -= kPas;
      }

      // Mémoire du saut : si on a appuyé un peu trop tôt, le saut part à l'atterrissage
      if (sautEnAttente > 0.f) {
         if (mario.OnGround()) {
            mario.Jump();
            sautEnAttente = 0.f;
         } else {
            sautEnAttente -= dt;
         }
      }

      // Gemmes : ramassées quand Mario touche leur capteur
      for (auto &g : gemmes)
         if (g.TryCollect())
         {
            std::println("Gemme ! Score : {}", ++score);
            majTitre();
         }

      if (mario.OnGround() != marioAuSol) {
         marioAuSol = mario.OnGround();
         std::println("{}", marioAuSol ? "Mario touche le sol" : "Mario est en l'air");   // le format doit être fixe
      }





      mario.Update();

      // Tombé hors de l'écran (sous la fenêtre ou trop loin sur un côté) : un essai en moins
      const sf::Vector2f pos = mario.GetScreenPosition();
      if (!gameOver && (pos.y > 850.f || pos.x < -50.f || pos.x > 1250.f)) {
         --essais;
         if (essais <= 0) {
            gameOver = true;
            std::println("GAME OVER ! Score final : {}. Appuie sur R pour rejouer.", score);
         } else {
            std::println("Perdu ! Il reste {} essai(s).", essais);
         }
         mario.Respawn(departMario);
         majTitre();
      }
      for (auto &m : sol) m.Update();
      for (auto &p : plateformes) p.Update();
      // falling.Update();
      // platform.Update();

      window.clear(sf::Color::Black);

      // La caméra suit Mario, sans jamais sortir du niveau (pas de bord noir)
      const sf::Vector2f demi = camera.getSize() / 2.f;
      const sf::Vector2f cible = mario.GetScreenPosition();
      camera.setCenter({std::clamp(cible.x, demi.x, 1200.f - demi.x),
                        std::clamp(cible.y, demi.y, 800.f - demi.y)});
      window.setView(camera);

      window.draw(mario);
      for (const auto &m : sol) window.draw(m);
      for (const auto &p : plateformes) window.draw(p);
      for (const auto &g : gemmes) window.draw(g);
      window.draw(arrivee);
      window.display();

   }


   b2DestroyWorld(monde);
   return EXIT_SUCCESS;
}
