#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1920, 1080}), "The Game" ,sf::Style::Default);
    window.setFramerateLimit(120);

    sf:: RectangleShape rect(sf::Vector2f(100, 100));
    rect.setFillColor(sf::Color::Blue);
    rect.setPosition({1,1});

    sf::Texture texture("Ressources/Cuphead_Run_03.png");
    sf::Sprite cuphead(texture);
    cuphead.setPosition({300.f, 300.f});

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                if (key->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
        }


        //GAME LOOP
        rect.move({1,1});


        window.clear(sf::Color::Black);
        window.draw(rect);
        window.draw(cuphead);
        window.display();
    }
}
