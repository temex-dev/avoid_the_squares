#include "Enemies.h"
#include "Player.h"

int Enemies::enemyCount = 0;

void Enemies::resetEnemyCount() {
    Enemies::enemyCount = 0;
}
int Enemies::getEnemyCount() {
    return enemyCount;
}
string Enemies::getName() const {
    return this->name;
}
int Enemies::getDamage() const {
    return this->damage;
}
void Enemies::generateName() {
    static vector<string> names;
    static bool loaded = false;

    if (!loaded) {
        ifstream file("../names.txt");
        string line;

        while (getline(file, line)) {
            if (!line.empty())
                names.push_back(line);
        }

        file.close();
        loaded = true;
    }

    if (!names.empty()) {
        int randomIndex = rand() % names.size();
        this->name = names[randomIndex];
    } else {
        this->name = "Unknown";
    }
}

void Enemies::draw(sf::RenderWindow& window) {
    string name = this->getName();
    sf::Text nameText(FONT);
    nameText.setString("");
    
    nameText.setPosition({ this->rectangle.getPosition().x, this->rectangle.getPosition().y - 45.f });
    nameText.setCharacterSize(30);
    nameText.setFillColor(sf::Color::White);
    nameText.setString(name);

    window.draw(nameText);
    window.draw(rectangle);

}
void Enemies::followPlayer(Player& player, vector<Enemies*> &enemies) {
    sf::Vector2f playerPos = player.getCircle().getPosition();
    sf::Vector2f enemyPos = rectangle.getPosition();
    sf::Vector2f move(0.f, 0.);

    if (playerPos.x > enemyPos.x) { move.x = ENEMY_SPEED; }
    else if (playerPos.x < enemyPos.x) { move.x = -ENEMY_SPEED; }

    if (playerPos.y > enemyPos.y) { move.y = ENEMY_SPEED; }
    else if (playerPos.y < enemyPos.y) { move.y = -ENEMY_SPEED; }

//check for collision with other enemies
//X axis
    rectangle.move({ move.x, 0.f });
    for (Enemies* other : enemies) {
        if (other == this) continue;
        if (rectangle.getGlobalBounds().findIntersection(
            other->rectangle.getGlobalBounds())) {
            rectangle.move({ -move.x, 0.f }); // undo X move
            break;
        }
    }

//Y axis
    rectangle.move({ 0.f, move.y });
    for (Enemies* other : enemies) {
        if (other == this) continue;
        if (rectangle.getGlobalBounds().findIntersection(
            other->rectangle.getGlobalBounds())) {
            rectangle.move({ 0.f, -move.y }); // undo Y move
            break;
        }
    }

}
sf::RectangleShape& Enemies::getRectangle() const {
    return const_cast<sf::RectangleShape&>(this->rectangle);
}
