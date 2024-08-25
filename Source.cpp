#include <iostream>

class Player {
private:
	int live;
	int power;
	int level;
	int exp;
public:
	Player();
	void changePower();
	void changeLevel();
	int getPower();
	int getLive();
	int getLevel();
	int getExp();
	int punch();
	void expUp(int);
};
Player::Player() {
	live = 100;
	power = 1;
	level = 1;
	exp = 0;
}
int Player::getLive() {
	return live;
}
int Player::getPower() {
	return power;
}
int Player::getLevel() {
	return level;
}
int Player::getExp() {
	return exp;
}
void Player::changeLevel() {
	if (exp > 5*level) {
		level++;
		exp = 0;
		changePower();
	}
}
void Player::changePower() {
	power = level * 2;
}
void Player::expUp(int cant) {
	exp += cant;
	changeLevel();
}
int Player::punch() {
	return power;
}
class Three {
private:
	int live;
	int level;
public:
	Three();
	void breaker(int);
	int muerte(int);
	int changeLevel();
	void mostrarArbol();
};
Three::Three(){
	live = 10;
	level = 1;
}
int Three::changeLevel() {
	if (live <= 0) {
		level++;
		live =10 + (2 * level);
		return muerte(level-1);
	}
	return 0;
}
int Three::muerte(int level) {
	return level*2;
}
void Three::breaker(int power) {
	live -= power;
}
void Three::mostrarArbol() {
	std::cout << "Vida: " << live << std::endl;
	std::cout << "level: " << level << std::endl;
}
int main() {
	Player p1;
	Three arbol_1;
	int election;
	bool cast=true;
	int experience;
	
	while (cast) {
		std::cout << "\tMenu" << std::endl;
		std::cout << "Escoge la opcion que prefieras\n1) Ver nivel\n2)Golpear\n3)Mostrar arbool\n4)finalizar acciones" << std::endl;
		std::cin >> election;
		switch (election) {
		case 1:
			std::cout << "Nivel: " << p1.getLevel() << std::endl;
			std::cout << "Experiencia: " << p1.getExp() << std::endl;
			std::cout <<"Fuerza: " << p1.getPower() << std::endl;
			break;
		case 2:
			arbol_1.breaker(p1.punch());
			experience = arbol_1.changeLevel();
			if ( experience== 0) {
				std::cout << "No recibiste experiencia" << std::endl;
			}
			else {
				std::cout << "Recibiste " << experience <<" de experiencia" << std::endl;
			}
			p1.expUp(experience);
			break;
		case 3:
			arbol_1.mostrarArbol();
			break;
		case 4:
			cast = false;
			break;
		default:
			std::cout << "No se encuentra tu elección, intentalo de nuevo" << std::endl;
			break;
		}
	}
	return 0;
}