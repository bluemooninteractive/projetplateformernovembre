#ifndef GAME_HPP
#define GAME_HPP

#include <optional>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>


class Game {
public:
    void initialize();
    void loop();

private:
    void processEvents();
    void render();

    sf::RenderWindow window;
    sf::Texture texture;
    std::optional<sf::Sprite> player;
};


#endif // GAME_HPP
