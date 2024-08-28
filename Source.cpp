#include <iostream>

class Player {
private:
	int live;
	int power;
	int level;
	int exp;
public:
	//Constructor
	Player(int);
	Player();
	//Cambia el atributo "level" utilizando el atributo "exp"
	void changeLevel();
	//Cambia el atributo "vida" dependiendo del argumento e imprime un mensaje
	void changeLive(int);
	//Getes
	int getPower();
	int getLive();
	int getLevel();
	int getExp();
	//Retorna "power"
	int punch();
	//Recibe una cantidad entera y la agrega al atributo "exp"
	void expUp(int);
	//Verifica el atributo "level", si level<=0, entonces llama al metodo renacer e imprime un mensaje y retorna "level"
	//si level>0, retorna 0;
	void muerte();
	//Vuelve los atributos "por defecto"
	void renacer();
	//
	void kill(int);
};
Player::Player(int live) {
	this->live = live;
	level = 1;
	power = 1;
	exp = 0;
}
Player::Player() {
	live = 12;
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
	if (exp >= 5*level) {
		level++;
		live =10 + (2*level);
		exp = 0;
		power = level * 2;
	}
}
void Player::expUp(int cant) {
	exp += cant;
	changeLevel();
}
int Player::punch() {
	return power;
}
void Player::changeLive(int change) {
	live += change;
	if (change > 0) {
		std::cout << "Recibiste "<<change<<" vida"<<std::endl;
	}
	else {
		std::cout << "Recibiste " << change << " daño" << std::endl;
		muerte();
	}
	
}
void Player::muerte() {
	if (live <= 0) {
		std::cout << "Has muerto, vas a renacer nivel 1"<<std::endl;
		renacer();
	}
}
void Player::renacer() {
	level = 0;
	changeLevel();
}
void Player::kill(int experience) {
	std::cout << "Has matado a un enemigo" << std::endl;
		expUp(experience+3);	
}

class Three {
private:
	int live;
	int level;
public:
	//Costructor
	Three();
	//Recibe un entero n y disminuye el atributo vida n veces
	void breaker(int);
	//Recibe un entero n y retorna dos veces n
	int muerte(int);
	//Comprueba si el atributo "live" es igual a cero, si live<=0, entonces aumenta "level" una unidad, "rellena" live mas dos veces "level" y retorna el metodo muerte con el argumento level-1
	// si live>0, retorna 0
	int changeLevel();
	//Muestra los atributos como cadena de texto
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
class Enemy {
private:
	int live;
	int power;
	int level;
	int exp;
	int kills;
	int deads;
public:
	//Constructor
	Enemy();
	//getes
	int getLive();
	int getPower();
	int getLevel();
	int getExp();
	int getKills();
	int getDeads();
	//Changes
	void changeLevel();
	void changeLive(int);
	//Hit
	int punch();
	//kill
	void kill();
	//dead
	void dead();
	//renacer
	void renacer();

};
Enemy::Enemy() {
	live = 15;
	power = 5;
	level = 1;
	exp = 0;
	kills = 0;
	deads = 0;
}
int Enemy::getLive() {
	return live;
}
int Enemy::getPower() {
	return power;
	}
int Enemy::getLevel() {
	return level;
}
int Enemy::getExp() {
	return exp;
}
int Enemy::getKills() {
	return kills;
}
int Enemy::getDeads() {
	return deads;
}
void Enemy::changeLevel() {
	level++;
	exp+=level*3;
	live = 15 + (level * 2);
	power = level * 3;
}
int Enemy::punch() {
	return power;
}
void Enemy::changeLive(int change) {
	if (change < 0) {
		std::cout << "Enemigo recibio " << change << " danio" << std::endl;
		dead();
	}
	live += change;
}
void Enemy::kill() {
	std::cout << "Has matado a un personaje" << std::endl;
	changeLevel();
}
void Enemy::dead() {
	if (live <= 0) {
		renacer();
		deads++;
	}
}
void Enemy::renacer() {
	level = 0;
	changeLevel();
}

int main() {
	Player player;
	Three arbol_1;
	Enemy enemigo;
	int election;
	bool cast=true;
	int experience;
	//Itera mientras cast==true
	while (cast) {
		std::cout << "\tMenu" << std::endl;
		std::cout << "Escoge la opcion que prefieras\n1)Ver nivel\n2)Golpear Arbol\n3)Golpear enemigo\n4)Mostrar arbool\n5)Mostrar enemigo\n6)finalizar acciones" << std::endl;
		std::cin >> election;
		//Comprueba el valor de la variable "election"
		switch (election) {
		case 1:
			//Imprime los gets del objeto player
			std::cout << "Vida: " << player.getLive() << std::endl;
			std::cout << "Nivel: " << player.getLevel() << std::endl;
			std::cout << "Experiencia: " << player.getExp() << std::endl;
			std::cout <<"Fuerza: " << player.getPower() << std::endl;
			break;
		case 2:
			//Llama al metodo "Three::breaker" con "Player::punch" como argumento
			arbol_1.breaker(player.punch());
			//Da valor a la variable "experience" el valor retornado de "Three::changeLevel"
			experience = arbol_1.changeLevel();
			//Imprime el valor de "experience", pero si es igual a cero, imprime otro mensaje
			if ( experience== 0) {
				std::cout << "No recibiste experiencia" << std::endl;
			}
			else {
				std::cout << "Recibiste " << experience <<" de experiencia" << std::endl;
				if (player.getLive() < 10 + (player.getLevel() * 2)) {
					player.changeLive(1);
				}
			}
			//Llama al metodo "Player::expUp" con el argumento "experience"
			player.expUp(experience);
			break;
		case 3:
			enemigo.changeLive(-player.punch());
			player.changeLive(-enemigo.punch());
			break;
		case 4:
			//Llama al metodo "Three::mostrarArbol"
			arbol_1.mostrarArbol();
			break;
		case 5:
			std::cout << "Nivel del enemigo: " << enemigo.getLevel() << std::endl;
			std::cout << "Vida del enemigo: " << enemigo.getLive() << std::endl;
			std::cout << "Fuerza del enemigo:	" << enemigo.getPower() << std::endl;
			break;
		case 6:
			//Finaliza el while, dantole valor de false a la variable "cast"
			cast = false;
			break;
		default:
			//Imprime un mensaje, si el valor de "election" es diferente a los casos disponibles
			std::cout << "No se encuentra tu elección, intentalo de nuevo" << std::endl;
			break;
		}
	}
	return 0;
}