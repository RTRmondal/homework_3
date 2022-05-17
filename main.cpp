#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <time.h>

void change_color(sf::RectangleShape &rectangle)
{
    rectangle.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    // create some shapes
    sf::CircleShape circle(100.0);
    circle.setPosition(0.0, 400.0);
    circle.setFillColor(sf::Color(100, 250, 50));

    sf::RectangleShape rectangle(sf::Vector2f(120.0, 60.0));
    rectangle.setPosition(0.0, 10.0);
    rectangle.setFillColor(sf::Color(100, 50, 250));

    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0.0, 0.0));
    triangle.setPoint(1, sf::Vector2f(0.0, 100.0));
    triangle.setPoint(2, sf::Vector2f(140.0, 40.0));
    triangle.setOutlineColor(sf::Color::Red);
    triangle.setOutlineThickness(5);
    triangle.setPosition(600.0, 100.0);

    sf::Clock clock;

    float rectangle_velocity_x = 150;
    float rectangle_velocity_y = 250;
    float rectangle_angular_velocity = 20;

    srand(time(NULL));


    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();

        rectangle.move(rectangle_velocity_x*elapsed.asSeconds(), rectangle_velocity_y*elapsed.asSeconds());
        rectangle.rotate(rectangle_angular_velocity*elapsed.asSeconds());

        sf::FloatRect rectangle_bounds = rectangle.getGlobalBounds();

        if(rectangle_bounds.top >= 600 - rectangle_bounds.height && rectangle_velocity_y > 0)
        {
            rectangle_velocity_y = -rectangle_velocity_y;
            change_color(rectangle);
        }
        else if(rectangle_bounds.left >= 800 - rectangle_bounds.width && rectangle_velocity_x > 0)
        {
            rectangle_velocity_x = -rectangle_velocity_x;
            change_color(rectangle);
        }
        else if(rectangle_bounds.top <= 0.0 && rectangle_velocity_y < 0) 
        {
            rectangle_velocity_y = -rectangle_velocity_y;
            change_color(rectangle);
        }
        else if(rectangle_bounds.left <= 0.0 && rectangle_velocity_x < 0)
        {
            rectangle_velocity_x = -rectangle_velocity_x;
            change_color(rectangle);
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);

        window.draw(circle);
        window.draw(rectangle);
        window.draw(triangle);

        // end the current frame
        window.display();
    }

    return 0;
}
