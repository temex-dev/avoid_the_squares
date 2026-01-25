#include "Enemies.h"
#include "Player.h"

int Enemies::enemyCount = 0;

string Enemies::getName() const {
    return this->name;
}
int Enemies::getDamage() const {
    return this->damage;
}
void Enemies::generateName() {
    vector<string> names;
    string line;
    ifstream file("../names.txt");
    
    while (getline(file, line)) {
        names.push_back(line);
    }
    file.close();

    if (!names.empty()) {
        srand(time(0));
        int randomIndex = rand() % names.size();
        this->name = names[randomIndex];
    }
}

int Enemies::getEnemyCount() {
    return enemyCount;
}
void Enemies::draw(sf::RenderWindow& window) {
    string name = this->getName();
    sf::Text nameText(FONT);
    
    nameText.setPosition({ this->rectangle.getPosition().x, this->rectangle.getPosition().y - 45.f });
    nameText.setCharacterSize(30);
    nameText.setFillColor(sf::Color::White);
    nameText.setString(name);

    window.draw(nameText);
    window.draw(rectangle);

}
void Enemies::followPlayer(Player& player) {
    sf::Vector2f playerPos = player.getCircle().getPosition();
    sf::Vector2f enemyPos = rectangle.getPosition();

    float x = 0.f, y = 0.f;

    if (playerPos.x > enemyPos.x) {
        x = ENEMY_SPEED;
    } else if (playerPos.x < enemyPos.x) {
        x = -ENEMY_SPEED;
    }

    if (playerPos.y > enemyPos.y) {
        y = ENEMY_SPEED;
    } else if (playerPos.y < enemyPos.y) {
        y = -ENEMY_SPEED;
    }

    rectangle.move({x, y});
}
sf::RectangleShape& Enemies::getRectangle() const {
    return const_cast<sf::RectangleShape&>(this->rectangle);
}