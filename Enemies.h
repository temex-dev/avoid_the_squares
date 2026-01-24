#ifndef ENEMIES_H
#define ENEMIES_H
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
        : name("N/A"), damage(damage), x(DEF_ENEMY_X), y(DEF_ENEMY_Y) {
            this->generateName();
            enemyCount++;
            this->rectangle.setSize({ENEMY_SIZE, ENEMY_SIZE});
            this->rectangle.setFillColor(sf::Color(RED_VEIN.r, RED_VEIN.g, RED_VEIN.b));
            this->rectangle.setPosition(sf::Vector2<float>(DEF_ENEMY_X, DEF_ENEMY_Y));
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