#include <SFML/Graphics.hpp>
#include "Scene/SceneManager.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "737R15!");
    sf::Clock clock;
    float updateTimer = 0.1;
    //GameScene* scene = new GameScene();
    SceneManager* manager = new SceneManager();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }
        window.clear();
        
        manager->update(clock.getElapsedTime().asSeconds());
        clock.restart();
        manager->draw(window, sf::RenderStates::Default);
        
        window.display();
    }

    //scene->Cleanup();
    delete manager;
    return 0;
}