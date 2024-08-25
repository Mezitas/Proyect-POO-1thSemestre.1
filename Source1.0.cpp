#include <iostream>

class Player {
private:
	int live;
	int power;
	int level;
	int exp;
public:
	Player();
	void setPower();
	void changeLevel();
	int getPower();
	int getLive();
	int getLevel();
	int getExp();
	void punch();
};
Player::Player() {
	live = 100;
	power = 1;
	level = 1;
	exp = 0;
}
void Player::changeLevel() {
	if (exp > 10*level) {
		level++;
		exp = 0;
	}
}
void Player::setPower() {
	power = level * 2;
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
void Player::punch() {
	std::cout << "Has golpeado, optienes 3 de experiencia" << std::endl;
	exp+=3;
	changeLevel();
}
int main() {
	Player p1;
	int election;
	bool cast=true;
	
	while (cast) {
		std::cout << "\tMenu" << std::endl;
		std::cout << "Escoge la opcion que prefieras\n1) Ver nivel\n2)Ver fuerza\n3)Golpear\n4)finalizar acciones" << std::endl;
		std::cin >> election;
		switch (election) {
		case 1:
			std::cout << "Nivel: " << p1.getLevel() << std::endl;
			std::cout << "Experiencia: " << p1.getExp() << std::endl;
			break;
		case 2:
			p1.setPower();
			std::cout <<"Fuerza: " << p1.getPower() << std::endl;
			break;
		case 3:
			p1.punch();
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
