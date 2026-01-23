#include "Player.h"
#include "Enemies.h"
#include "globals.h"
#include <SFML/Graphics/Text.hpp>

bool start = true;

int main() {
    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}),
            "Avoid the Squares",
            sf::Style::Default,
            sf::State::Windowed);
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    window.setPosition({(DISPLAY_WIDTH / 2) - WINDOW_SIZE / 2, (DISPLAY_HEIGHT / 2) - WINDOW_SIZE / 2} );
    window.setFramerateLimit(60);


    auto *pPlayer = new Player("Hero", 100, window);
    auto *pEnemy1 = new Enemies(20, window);

    sf::Clock gameClock;
    sf::Font font("../resources/OMORI_GAME.ttf");
    sf::Text clock(font);
    clock.setPosition( {WINDOW_SIZE / 2.f - 50.f, 10.f} );


//game loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

//waiting first 3 seconds before starting the game
        window.clear(sf::Color(GREEN_VEIN.r, GREEN_VEIN.g, GREEN_VEIN.b)); //settings background color
        if (start) {
            string word = "Game stars in ";
            sf::Text text(font);
            text.setPosition({ WINDOW_SIZE / 2.8f, WINDOW_SIZE / 5.f });
            text.setCharacterSize(50);
            text.setFillColor(sf::Color::White);
            for (int i = 3; i > 0; i--) {
                text.setString(word + to_string(i));
                window.draw(text);
                window.display();
                sf::sleep(sf::seconds(1));
                window.clear(sf::Color(GREEN_VEIN.r, GREEN_VEIN.g, GREEN_VEIN.b));
                gameClock.restart();
            }
            start = false; 
        }
//timer
        int elapsed = gameClock.getElapsedTime().asMilliseconds();
        int minutes = elapsed / 60000;
        int seconds = elapsed / 1000 % 60;
        int milliseconds = elapsed % 1000;
        clock.setString(to_string(minutes) + ":" + to_string(seconds) + ":" + to_string(milliseconds));

//player movement1
        pPlayer->movement(pPlayer->getCircle());

//enemy movement
        pEnemy1->followPlayer(*pPlayer);

//detect collision
        if (pPlayer->detectCollision(*pEnemy1) == true){
            pPlayer->takeDamage(pEnemy1->getDamage());
            cout << "Health: " << pPlayer->getHealth() << endl;
            cout << "Is alive? " << pPlayer->isAlive() << endl;
        }

//drawing on screen
        pPlayer->draw(window);
        pEnemy1->draw(window);
        window.draw(clock);
        window.display();
    }
    return 0;
}
