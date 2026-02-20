#include "Player.h"
#include "Enemies.h"
#include "globals.h"
#include <SFML/Audio/Sound.hpp>

int main() {
// Game CLI menu
    string name;
    int health;
    int damage;
    char choice;

    cout << "Avoid The Squares\n";
    cout << "Instructions:\n";
    cout << "1. Use WASD keys to move your character (the circle).\n";
    cout << "2. Avoid the red squares (enemies) that will follow you.\n";
    cout << "3. Every 15 seconds, a new enemy will be added to the game.\n";
    cout << "4. If an enemy touches you, you will lose health. The game ends when your health reaches zero.\n";
    cout << "5. Try to survive as long as possible and see how long you can last!\n";
    cout << "Press 'Enter' to continue...";
    cin.get();
    cout << "Enter your name: ";
    getline(cin, name);
    cout << "Press 'D' to play with default settings or 'C' for custom settings\n";
    cin >> choice;
    if (choice == 'C' || choice == 'c') {
        cout << "Enter player health (default " << DEF_PLAYER_HEALTH << "(might be buggy with higher values)): ";
        cin >> health;
        cout << "Enter enemy damage (default " << DEF_ENEMY_DAMAGE << "): ";
        cin >> damage;
    }
    else if (choice == 'D' || choice == 'd') {
        health = DEF_PLAYER_HEALTH;
        damage = DEF_ENEMY_DAMAGE;
    }
    else {
        cout << "Invalid choice. Using default settings.\n";
        health = DEF_PLAYER_HEALTH;
        damage = DEF_ENEMY_DAMAGE;
    }

    sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}),
            "Avoid the Squares",
            sf::Style::Default,
            sf::State::Windowed);    
    window.setFramerateLimit(60);
    window.setPosition({(DISPLAY_WIDTH / 2) - WINDOW_SIZE / 2, (DISPLAY_HEIGHT / 2) - WINDOW_SIZE / 2} );
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    bool gameRunning = true;
    
    while (gameRunning) {
        bool start = true;
        vector<Enemies*> enemies;

        sf::Clock gameClock;
        sf::Clock enemySpawnClock;
        sf::Text clock(FONT);
        clock.setString("");
        clock.setPosition({WINDOW_SIZE / 2.f - 20.f, 10.f});

//danger zone
        sf::RectangleShape dangerZone;
        dangerZone.setSize({50.f, 50.f});
        dangerZone.setFillColor(sf::Color(sf::Color::Red));
        dangerZone.setPosition({DEF_ENEMY_X - 5.f, DEF_ENEMY_Y});

//number of enemies
        sf::Text enemyCount(FONT);
        enemyCount.setPosition({10.f, 10.f});
        enemyCount.setCharacterSize(24);
        enemyCount.setFillColor(sf::Color::White);

        bool gameOver = false;

        auto *pPlayer = new Player(name, health, window);
        auto *pEnemy = new Enemies(damage, window);
        enemies.push_back(pEnemy);

//game loop
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
//starter screen     
                if (start) {
                    string word = "Game stars in ";
                    sf::Text text(FONT);
                    sf::Text hint(FONT);
                    hint.setPosition({ WINDOW_SIZE / 2.8f - 50.f, WINDOW_SIZE / 5.f - 60.f });
                    hint.setCharacterSize(30);
                    hint.setFillColor(sf::Color::White);
                    hint.setString("Every 15s an enemy will be added.");
                    
                    text.setPosition({ WINDOW_SIZE / 2.8f, WINDOW_SIZE / 5.f });
                    text.setCharacterSize(50);
                    text.setFillColor(sf::Color::White);
                    for (int i = 3; i > 0; i--) {
                        text.setString(word + to_string(i));
                        window.draw(text);
                        window.draw(hint);
                        window.display();
                        sf::sleep(sf::seconds(1));
                        window.clear(sf::Color(GREEN_VEIN.r, GREEN_VEIN.g, GREEN_VEIN.b));
                    }
                    start = false;
                    gameClock.restart();
                    enemySpawnClock.restart();
                }

//timer
                int elapsed = gameClock.getElapsedTime().asMilliseconds();
                int minutes = elapsed / 60000;
                int seconds = (elapsed / 1000) % 60;
                int milliseconds = elapsed % 1000;

                string timeStr = "";
                if (minutes < 10) {timeStr += "0";}
                timeStr += to_string(minutes) + ":";
                if (seconds < 10) {timeStr += "0";}
                timeStr += to_string(seconds) + ":";
                if (milliseconds < 100) {timeStr += "0";}
                if (milliseconds < 10) {timeStr += "0";}
                timeStr += to_string(milliseconds);
                clock.setString(timeStr); 

//spawn new enemy every 15s
                if (enemySpawnClock.getElapsedTime().asSeconds() >= 15.f) {
                    auto *newEnemy = new Enemies(damage, window);
                    enemies.push_back(newEnemy);
                    enemySpawnClock.restart();
                }
//player movement
                pPlayer->movement(pPlayer->getCircle());
//enemy movement
                for (Enemies* enemy : enemies) {
                    enemy->followPlayer(*pPlayer, enemies);
                }

//collision detection
                for (Enemies* enemy : enemies) {
                    if (pPlayer->detectCollision(*enemy)) {
                        pPlayer->takeDamage(enemy->getDamage());
                    }
                }
                
//drawing on screen
                enemyCount.setString("Enemies: " + to_string(Enemies::getEnemyCount()));
                window.draw(dangerZone);
                pPlayer->draw(window, (float)health);
                for (Enemies* enemy : enemies) {
                    enemy->draw(window);
                }
                window.draw(clock);
                window.draw(enemyCount);
                window.display();
            }
            else {
// Game over screen
                window.clear(sf::Color::Black);
                sf::Text gameOverText(FONT);
                sf::Text instruction(FONT);
                sf::Text time(FONT);
                sf::Text killer(FONT);

                gameOverText.setPosition({ WINDOW_SIZE / 3.f + 20.f, WINDOW_SIZE / 3.f });
                gameOverText.setCharacterSize(70);
                gameOverText.setFillColor(sf::Color::Red);
                gameOverText.setString("Game Over!");

                killer.setPosition({ WINDOW_SIZE / 3.f + 50.f, WINDOW_SIZE / 2.f - 50.f });
                killer.setCharacterSize(30);
                killer.setFillColor(sf::Color::White);
                killer.setString("Killed by: " + LAST_HIT);

                instruction.setPosition({ WINDOW_SIZE / 3.f, WINDOW_SIZE - 50.f });
                instruction.setCharacterSize(30);
                instruction.setFillColor(sf::Color::White);
                instruction.setString("Press 'Enter' to restart or 'Esc' to exit.");
                
                time.setPosition({ WINDOW_SIZE / 3.f + 50.f, WINDOW_SIZE / 2.f });
                time.setCharacterSize(30);
                time.setFillColor(sf::Color::White);
                string finalTime = clock.getString().toAnsiString();
                time.setString("Your time: " + finalTime);

                window.draw(killer);
                window.draw(gameOverText);
                window.draw(instruction);
                window.draw(time);
                window.display();

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                    gameOver = true;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                    gameRunning = false;
                    gameOver = true;
                }
            }
        }
//ending program / restarting
        delete pPlayer;
        for (Enemies* enemy : enemies) {
            delete enemy;
        }
        enemies.clear();
        Enemies::resetEnemyCount();
    }
    return 0;
}
