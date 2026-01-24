#include "Player.h"
#include "Enemies.h"
#include "globals.h"
#include <cstdlib>


int main() {
    bool gameRunning = true;

    while (gameRunning) {
        bool start = true;
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
        clock.setPosition( {WINDOW_SIZE / 2.f - 20.f, 10.f} );

        bool gameOver = false;

        while (window.isOpen() && !gameOver) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                    gameRunning = false;
                    gameOver = true;
                }
            }

            if (pPlayer->isAlive()) {
                window.clear(sf::Color(GREEN_VEIN.r, GREEN_VEIN.g, GREEN_VEIN.b));
                
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

                int elapsed = gameClock.getElapsedTime().asMilliseconds();
                int minutes = elapsed / 60000;
                int seconds = elapsed / 1000 % 60;
                int milliseconds = elapsed % 1000;
                clock.setString(to_string(minutes) + ":" + to_string(seconds) + ":" + to_string(milliseconds));
                
                pPlayer->movement(pPlayer->getCircle());
                pEnemy1->followPlayer(*pPlayer);
                
                if (pPlayer->detectCollision(*pEnemy1) == true){
                    pPlayer->takeDamage(pEnemy1->getDamage());
                    cout << "Health: " << pPlayer->getHealth() << endl;
                    cout << "Is alive? " << pPlayer->isAlive() << endl;
                }
                
                pPlayer->draw(window);
                pEnemy1->draw(window);
                window.draw(clock);
                window.display();
            }
            else {
// Game over screen
                window.clear(sf::Color::Black);
                sf::Text gameOverText(font);
                sf::Text instruction(font);
                sf::Text time(font);
                gameOverText.setPosition({ WINDOW_SIZE / 3.f + 20.f, WINDOW_SIZE / 3.f });
                gameOverText.setCharacterSize(70);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setString("Game Over!");

                instruction.setPosition({ WINDOW_SIZE / 3.f, WINDOW_SIZE - 50.f });
                instruction.setCharacterSize(30);
                instruction.setFillColor(sf::Color::White);
                instruction.setString("Press 'Enter' to restart or 'Esc' to exit.");
                
                time.setPosition({ WINDOW_SIZE / 3.f + 50.f, WINDOW_SIZE / 2.f });
                time.setCharacterSize(30);
                time.setFillColor(sf::Color::White);
                time.setString("Your time: " + clock.getString());

                window.draw(gameOverText);
                window.draw(instruction);
                window.draw(time);
                window.display();
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                    gameOver = true;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                    delete pPlayer;
                    delete pEnemy1;
                    exit(0);
                }
            }
        }

        delete pPlayer;
        delete pEnemy1;
    }

    return 0;
}
