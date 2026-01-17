#include "Player.h"

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
bool Player::isAlive() const {
    return this->health > 0;
}

void Player::moveRight(sf::CircleShape& circle) {
    circle.move({5.f, 0.f});
}
void Player::moveLeft(sf::CircleShape& circle) {
    circle.move({-5.f, 0.f});
}
void Player::moveUp(sf::CircleShape& circle) {
    circle.move({0.f, -5.f});
}
void Player::moveDown(sf::CircleShape& circle) {
    circle.move({0.f, 5.f});
}
void Player::draw(sf::RenderWindow& window) {
    window.draw(circle);
}
sf::CircleShape& Player::getCircle() const {
    return const_cast<sf::CircleShape&>(this->circle);
}
