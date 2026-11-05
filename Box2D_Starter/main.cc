#include <cstdlib>
#include <print>
#include <box2d/box2d.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "include/constants.hpp"
#include "include/entity.hpp"
#include "include/physical_object.hpp"
#include "include/contacts.hpp"

int main() {

   b2WorldDef def = b2DefaultWorldDef();
   def.gravity = {0.f, 0.68f};

   b2WorldId monde = b2CreateWorld(&def);

   sf::RenderWindow window(sf::VideoMode({1200, 800}), "Physics", sf::Style::Default);
   window.setFramerateLimit(240);

   constexpr double kPas = 1000.f / 60.f;
   constexpr int kSousPas = 4;
   double accumulateur_ = 0.0f;

   sf::Clock clock;
   double dt;

   Entity mario;
   mario.Setup(sf::Color::Red, {30,30});
   mario.SetupPhysics(monde, b2_dynamicBody, {1,1}, true);   // true : avec un capteur de sol (pour sauter)
   bool marioAuSol = false;

   Entity platform;
   platform.Setup(sf::Color::Yellow, {1200,30});                       // en pixels : toute la largeur de la fenêtre
   platform.SetupPhysics(monde, b2_staticBody,                         // en mètres : le CENTRE de la barre
      {Conversions::ScreenToPhysics(600.f), Conversions::ScreenToPhysics(785.f)});   // milieu en x, tout en bas en y (800 - 30/2)

   while (window.isOpen()) {

      dt = clock.restart().asMilliseconds();
      accumulateur_ += dt;

      while (const std::optional event = window.pollEvent()) {
         if (event->is<sf::Event::Closed>()) {
            window.close();
         }

         // le saut : un événement, pour qu'un appui donne un seul saut (pas un rebond tant qu'on garde la touche)
         if (const auto* touche = event->getIf<sf::Event::KeyPressed>()) {
            if (touche->code == sf::Keyboard::Key::Space) {
               mario.Jump();
            }
         }
      }

      // gauche / droite : tant que la touche est enfoncée
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
         mario.Left();
      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
         mario.Right();
      else
         mario.CancelMovement();   // aucune flèche : il s'arrête

      while (accumulateur_ >= kPas)
      {
         b2World_Step(monde, kPas / 1000.f, kSousPas);
         SensorsContact(monde);
         accumulateur_ -= kPas;
      }

      if (mario.OnGround() != marioAuSol) {
         marioAuSol = mario.OnGround();
         std::println("{}", marioAuSol ? "Mario touche le sol" : "Mario est en l'air");   // le format doit être fixe
      }




      mario.Update();
      platform.Update();
      // falling.Update();
      // platform.Update();

      window.clear(sf::Color::Black);
      window.draw(mario);
      window.draw(platform);
      window.display();

   }

   return EXIT_SUCCESS;
}
