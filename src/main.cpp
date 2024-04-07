#include <SFML/Graphics.hpp>

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktopMode, "Realm Explorer", sf::Style::Default, settings);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(window.getSize().x / 2 - shape.getRadius(), window.getSize().y / 2 - shape.getRadius());

    float moveSpeed = 5.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            shape.move(-moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            shape.move(moveSpeed, 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            shape.move(0, -moveSpeed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            shape.move(0, moveSpeed);
        }

        if (shape.getPosition().x < 0)
        {
            shape.setPosition(0, shape.getPosition().y);
        }
        if (shape.getPosition().x > window.getSize().x - shape.getRadius() * 2)
        {
            shape.setPosition(window.getSize().x - shape.getRadius() * 2, shape.getPosition().y);
        }
        if (shape.getPosition().y < 0)
        {
            shape.setPosition(shape.getPosition().x, 0);
        }
        if (shape.getPosition().y > window.getSize().y - shape.getRadius() * 2)
        {
            shape.setPosition(shape.getPosition().x, window.getSize().y - shape.getRadius() * 2);
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}