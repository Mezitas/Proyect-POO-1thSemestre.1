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
	//Cambia el atributo "power" respecto al atributo "level"
	void changePower();
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
	int muerte();
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
	live = 10;
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
		live =10 + (2*level);
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
void Player::changeLive(int change) {
	if (change > 0) {
		std::cout << "Recibiste"<<change<<" vida"<<std::endl;
	}
	else {
		std::cout << "Recibiste" << change << "daño" << std::endl;
	}
	live += change;
}
int Player::muerte() {
	if (live <= 0) {
		std::cout << "Has muerto, vas a renacer nivel 1"<<std::endl;
		return level;
		renacer();
	}
	return 0;
}
void Player::renacer() {
	live = 10;
	level = 1;
	power = 1;
	exp = 0;
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

int main() {
	Player player;
	Player enemigo(15);
	Three arbol_1;
	int election;
	bool cast=true;
	int experience;
	int kill;
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
				player.changeLive(1);
			}
			//Llama al metodo "Player::expUp" con el argumento "experience"
			player.expUp(experience);
			break;
		case 3:
			enemigo.changeLive(-player.punch());
			kill = enemigo.muerte();
			if (kill > 0) {
				player.kill(kill);
			}
			else {
				player.changeLive(-enemigo.punch());
				player.muerte();
			}
			break;
		case 4:
			//Llama al metodo "Three::mostrarArbol"
			arbol_1.mostrarArbol();
			break;
		case 5:
			std::cout << "Vida: " << enemigo.getLive() << std::endl;
			std::cout << "Nivel: " << enemigo.getLevel() << std::endl;
			std::cout << "Experiencia: " <<enemigo.getExp() << std::endl;
			std::cout << "Fuerza: " << enemigo.getPower() << std::endl;
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