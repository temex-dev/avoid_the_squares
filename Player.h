#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include "globals.h"

class Enemies;

class Player {
private:
    string name;
    int health;
    int x, y;
    sf::CircleShape circle;
    sf::Clock damageCooldown;
public:
    Player(const string &name, int health, sf::RenderWindow& window)
        : name(name), health(health), x(window.getSize().x / 2), y(window.getSize().y / 2) {
            this->circle.setRadius(PLAYER_SIZE);
            this->circle.setFillColor(sf::Color(WHITE_VEIN.r, WHITE_VEIN.g, WHITE_VEIN.b));
            this->circle.setPosition(sf::Vector2<float>(((float)WINDOW_SIZE / 2) - PLAYER_SIZE, 200.f));
            this->damageCooldown.restart();
            cout << "Player " << this->name << " created with " << this->health << " health at x,y: " << this->x << "," << this->y << ".\n";

    }

    ~Player() = default;

    [[nodiscard]] sf::CircleShape& getCircle() const;

    [[nodiscard]] string getName() const;
    [[nodiscard]] int getHealth() const;
    [[nodiscard]] bool isAlive() const;
    
    void moveRight(sf::CircleShape& circle);
    void moveLeft(sf::CircleShape& circle);
    void moveUp(sf::CircleShape& circle);
    void moveDown(sf::CircleShape& circle);
    void movement(sf::CircleShape& circle);
    void draw(sf::RenderWindow& window);

    [[nodiscard]] bool detectCollision(Enemies& enemy) const;
    void takeDamage(int damage);
};


#endif // PLAYER_H
