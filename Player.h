#ifndef PLAYER_H
#define PLAYER_H


#include "globals.h"


class Player {
private:
    string name;
    int health;
    int x, y;
    sf::CircleShape circle;
public:
    Player(const string &name, int health, sf::RenderWindow& window)
        : name(name), health(health), x(window.getSize().x / 2), y(window.getSize().y / 2) {
        cout << "Player " << this->name << " created with " << this->health << " health at x,y: " << this->x << "," << this->y << ".\n";
        
        this->circle.setRadius(20.f);
        this->circle.setFillColor(sf::Color(WHITE_VEIN.r, WHITE_VEIN.g, WHITE_VEIN.b));
        this->circle.setPosition(sf::Vector2<float>(this->x, this->y));
    }

    ~Player() = default;

    [[nodiscard]] sf::CircleShape& getCircle() const;

    [[nodiscard]] string getName() const;
    [[nodiscard]] int getHealth() const;
    void takeDamage(int damage);
    [[nodiscard]] bool isAlive() const;

    void moveRight(sf::CircleShape& circle);
    void moveLeft(sf::CircleShape& circle);
    void moveUp(sf::CircleShape& circle);
    void moveDown(sf::CircleShape& circle);
    void draw(sf::RenderWindow& window);
};


#endif // PLAYER_H
