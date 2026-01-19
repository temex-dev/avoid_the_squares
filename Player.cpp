#include "Player.h"
#include "Enemies.h"
#include <SFML/System/Vector2.hpp>

string Player::getName() const {
    return this->name;
}
int Player::getHealth() const {
    return this->health;
}
void Player::takeDamage(int damage) {
    this->health -= damage;
    if (this->health < 0) {
        this->health = 0;
    }
}
bool Player::detectCollision(Enemies& enemy) const {
    const sf::Vector2<float> playerPos = this->circle.getPosition();
    const sf::Vector2<float> enemyPos = enemy.getRectangle().getPosition();

    if (playerPos.x == enemyPos.x && playerPos.y == enemyPos.y) {
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
    window.draw(circle);
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
