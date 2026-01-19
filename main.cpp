#include "Player.h"
#include "Enemies.h"
#include "globals.h"

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


//game loop
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }


//player movement
        pPlayer->movement(pPlayer->getCircle());

//enemy movement
        pEnemy1->followPlayer(*pPlayer);

//detect collision
        if (pPlayer->detectCollision(*pEnemy1) == true){
            cout << pPlayer->detectCollision(*pEnemy1) << endl;
        }

//drawing on screen
        window.clear(sf::Color(GREEN_VEIN.r, GREEN_VEIN.g, GREEN_VEIN.b)); //settings background color
        pPlayer->draw(window);
        pEnemy1->draw(window);
        window.display();
        if (start) {sf::sleep(sf::seconds(3)); start = false; }
    }
    return 0;
}
