#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class Game
{
public:
    Game();
    void loop();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
    sf::Texture cupheadTexture;
    std::unique_ptr<sf::Sprite> cuphead;
};

#endif // GAME_HPP
