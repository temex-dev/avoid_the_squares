#ifndef ENEMIES_H
#define ENEMIES_H
#include <SFML/Graphics/RectangleShape.hpp>
#pragma once

#include "globals.h"

class Player;

class Enemies {
private:
    string name;
    int damage;
    int x, y;
    sf::RectangleShape rectangle;

    static int enemyCount;
public:
    Enemies(int damage, const sf::RenderWindow& window)
        : name("N/A"), damage(damage), x(window.getSize().x / 2), y(window.getSize().y / 2) {
            this->generateName();
            enemyCount++;
            this->rectangle.setSize({ENEMY_SIZE, ENEMY_SIZE});
            this->rectangle.setFillColor(sf::Color(RED_VEIN.r, RED_VEIN.g, RED_VEIN.b));
            this->rectangle.setPosition(sf::Vector2<float>(((float)WINDOW_SIZE / 2) - (ENEMY_SIZE / 2), 600.f));
            cout << "Enemy " << this->name << " created with " << this->damage << " damage at x,y: "<< this->x << "," << this->y << ".\n";
    }

    ~Enemies() = default;

    [[nodiscard]] sf::RectangleShape& getRectangle() const;
    [[nodiscard]] string getName() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] static int getEnemyCount();

    void generateName();
    void followPlayer(Player& player);
    void draw(sf::RenderWindow& window);
};


#endif // ENEMIES_H