#include "Enemies.h"
#include <SFML/Graphics/RenderWindow.hpp>

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
    window.draw(rectangle);

}
void Enemies::followPlayer() {
    
}