#include "Player.h"
#include "Enemies.h"

string LAST_HIT;

string Player::getName() const {
    return this->name;
}
int Player::getHealth() const {
    return this->health;
}
void Player::takeDamage(int damage) {
    if (this->damageCooldown.getElapsedTime().asSeconds() >= 1.0f) {
        this->health -= damage;
        if (this->health < 0) {
            this->health = 0;
        }
        this->damageCooldown.restart();
    }
}
bool Player::detectCollision(Enemies& enemy) const {
    const sf::Vector2<float> playerPos = this->circle.getPosition();
    const sf::Vector2<float> enemyPos = enemy.getRectangle().getPosition();

    if (playerPos.x + PLAYER_SIZE >= enemyPos.x &&
        playerPos.x - PLAYER_SIZE <= enemyPos.x + ENEMY_SIZE &&
        playerPos.y + PLAYER_SIZE >= enemyPos.y &&
        playerPos.y - PLAYER_SIZE <= enemyPos.y + ENEMY_SIZE) {
        LAST_HIT = enemy.getName();
        return true;
    }


    return false;
}

bool Player::isAlive() const {
    return this->health > 0;
}

void Player::moveRight(sf::CircleShape& circle) {
    circle.move({PLAYER_SPEED, 0.f});
}
void Player::moveLeft(sf::CircleShape& circle) {
    circle.move({-PLAYER_SPEED, 0.f});
}
void Player::moveUp(sf::CircleShape& circle) {
    circle.move({0.f, -PLAYER_SPEED});
}
void Player::moveDown(sf::CircleShape& circle) {
    circle.move({0.f, PLAYER_SPEED});
}
void Player::draw(sf::RenderWindow& window) {
    string name = this->getName();
    sf::RectangleShape healthBackground;
    sf::RectangleShape healthForeground;
    sf::Text nameText(FONT);

    nameText.setPosition({ this->circle.getPosition().x - 25.f, this->circle.getPosition().y - 45.f });
    nameText.setCharacterSize(30);
    nameText.setFillColor(sf::Color::White);
    nameText.setString(name);

    healthBackground.setSize({100.f, 10.f});
    healthBackground.setFillColor(sf::Color::Red);
    healthBackground.setPosition({ this->circle.getPosition().x - 25.f, this->circle.getPosition().y - 15.f });

    healthForeground.setSize({ (float)(this->getHealth()), 10.f });
    healthForeground.setFillColor(sf::Color::Green);
    healthForeground.setPosition({ this->circle.getPosition().x - 25.f, this->circle.getPosition().y - 15.f });

    window.draw(nameText);
    window.draw(circle);
    window.draw(healthBackground);
    window.draw(healthForeground);
}
sf::CircleShape& Player::getCircle() const {
    return const_cast<sf::CircleShape&>(this->circle);
}

void Player::movement(sf::CircleShape& circle) {
//movement controls
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this->moveLeft(circle);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this->moveRight(circle);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this->moveUp(circle);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this->moveDown(circle);
    }

//wrapping around the screen
    // Wrap around horizontally
    if (circle.getPosition().x > WINDOW_SIZE) {
        circle.setPosition({0.f, circle.getPosition().y});
    }
    if (circle.getPosition().x < -PLAYER_SIZE * 2) {
        circle.setPosition({WINDOW_SIZE, circle.getPosition().y});
    }
    // Wrap around vertically
    if (circle.getPosition().y > WINDOW_SIZE) {
        circle.setPosition({circle.getPosition().x, 0.f});
    }
    if (circle.getPosition().y < -PLAYER_SIZE * 2) {
        circle.setPosition({circle.getPosition().x, WINDOW_SIZE});
    }
}
