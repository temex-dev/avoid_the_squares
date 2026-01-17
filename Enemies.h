#ifndef ENEMIES_H
#define ENEMIES_H


#include "globals.h"
#include "Player.h"

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
        cout << "Enemy " << this->name << " created with " << this->damage << " damage at x,y: "<< this->x << "," << this->y << ".\n";
        enemyCount++;

        this->rectangle.setSize({40.f, 40.f});
        this->rectangle.setFillColor(sf::Color(RED_VEIN.r, RED_VEIN.g, RED_VEIN.b));
        this->rectangle.setPosition(sf::Vector2<float>(this->x, this->y));
    }

    ~Enemies() = default;

    [[nodiscard]] string getName() const;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] static int getEnemyCount();

    void generateName();
    void followPlayer(Player& player);
    void draw(sf::RenderWindow& window);
};


#endif // ENEMIES_H