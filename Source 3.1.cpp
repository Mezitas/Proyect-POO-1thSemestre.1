#include <iostream>
#include <cstdlib>
#include <string>

// códigos ACSI para el color
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define LBLUE "\x1B[38;2;53;149;240m"
#define LGREEN  "\x1B[38;2;17;245;120m"
#define GREY "\x1B[38;2;176;174;174m"
#define MAGENTA "\x1b[35m"
#define ORANGE "\x1B[38;2;255;128;0m"
#define RESET "\033[0m"

using namespace std;

// Clase base
class GameEntity {
protected:
	int life;
	int exp;
	int level;

public:
	GameEntity(int initialLife, int initialExp, int initialLevel)
		: life(initialLife), exp(initialExp), level(initialLevel) {
	}

	virtual ~GameEntity() = default;

	// Getters
	int getLife() { return life; }
	int getExp() { return exp; }
	int getLevel() { return level; }

	// Setters
	void setLife(int newLife) { life = newLife; }

	// Métodos virtuales
	virtual void upLevel() = 0;
	virtual int reduceLife(int value) = 0;
};

// Clase Enemy 
class Enemy : public GameEntity {
	int power;

public:
	Enemy() : GameEntity(20, 10, 1), power(3) {}

	// Getters y Setters de Enemy
	int getPower() { return power; }
	void setPower(int newPower) { power = newPower; }

	void upLevel() override {
		level++;
		life = 20 + (5 * level);
		exp = 10 + (5 * level);
		power = 3 + (5 * level);
	}

	int reduceLife(int value) override {
		life += value;
		return life;
	}

	int deadEnemy(int damage) {
		int devolution = 0;
		if (reduceLife(-damage) < 0) {
			upLevel();
			devolution = exp;
		}
		return devolution;
	}

	void KillEnemy(int reduceLife) {
		if (reduceLife <= 0) {
			life = 20 + (5 * level);
			exp = 10 + (5 * level);
			power = 3 + (5 * level);
		}
	}
	int fight() {
		int critical = power;
		int punch = rand() % 2 + 1;
		switch (punch)
		{
		case 2:
			critical *= 2;
			break;
		default:
			break;
		}
		return critical;
	}
};

// Clase Three 
class Three : public GameEntity {
public:
	Three() : GameEntity(10, 5, 1) {}

	void upLevel() override {
		level++;
		life = 10 + (2 * level);
		exp = 5 + (2 * level);
	}

	int reduceLife(int value) override {
		life += value;
		return life;
	}

	int deadThree(int damage) {
		int devolution = 0;
		if (reduceLife(damage) <= 0) {
			devolution = exp;
			upLevel();
		}
		return devolution;
	}
};

// Clase Player 
class Player {
private:
	int life;
	int level;
	int power;
	int exp;
	int kill;
	int dead;
	Three* myThree;
	Enemy* myEnemy;


	void changeProperties() {
		life = 10 + (level * 2);
		power = 2 + level;
		exp = 0;
	}

public:
	Player(Three* three, Enemy* enemy)
		: life(10), level(1), power(2), exp(0), kill(0), dead(0), myThree(three), myEnemy(enemy) {
	}

	~Player() {
		cout << "El jugador ha sido eliminado" << endl;
	}

	// Getters
	int getLife() { return life; }
	int getPower() { return power; }
	int getExp() { return exp; }
	int getLevel() { return level; }
	int getKill() { return kill; }
	int getDead() { return dead; }

	// Setters
	void setLife(int value) { life = value; }
	void setPower(int value) { power = value; }
	void setExp(int value) { exp = value; }
	void setLevel(int value) { level = value; }
	void setKill(int value) { kill = value; }
	void setDead(int value) { dead = value; }

	void upLevel() {
		if (exp >= level * 5) {
			level++;
			changeProperties();
		}
	}

	int hitThree() {
		int value = myThree->deadThree(-power);
		return value;
	}

	void upLevelThree() {
		int newValue = hitThree();
		if (newValue > 0) {
			exp += newValue;
			upLevel();
		}
	}

	int hitEnemy() {
		int value = fight();
		return value;
	}

	int takeDamage() {
		int damage = myEnemy->fight();
		return damage;
	}

	int deadPlayer(int value) {
		life -= value;
		if (life <= 0) {
			myEnemy->KillEnemy(life);
			life = 10;
			power = 2;
			exp = 0;
			level = 1;
			dead++;
			value = 0;
		}
		return value;
	}

	void upLevelEnemy(int damage) {
		int experience = myEnemy->deadEnemy(-damage);
		if (experience > 0) {
			exp += experience;
			kill++;
			upLevel();
		}
	}

	int fight() {
		int critical = power;
		int punch = rand() % 2+1;
		switch (punch)
		{
		case 2:
			critical *= 2;
			break;
		default:
			break;
		}
		return critical;
	}
};

// Menús
void PauseMenu() {
	system("pause");
	system("cls");
}

void loadingBar(const std::string& message, int steps = 15, int delay = 8000) {
		cout << message << " [";
		for (int i = 0; i < steps; ++i) {
			cout << "=" << std::flush;
			
			// Simulación de retraso usando un bucle vacío
			for (volatile int j = 0; j < delay * 10000; ++j);
			
		}
		cout << "] Completado!" << std::endl;
	}


int menuFightPlayer(Player* player) {
	int damage = player->fight();
	loadingBar("Iniciando pelea...");
	cout << BLUE << "--------------------------------" << RESET << endl;
	cout << LBLUE << "TURNO DEL JUGADOR" << LBLUE << endl;
	cout << BLUE << "--------------------------------" << RESET << endl;
	cout << LGREEN << "Daño hecho:___ " << RESET << damage << endl;
	cout << BLUE << "--------------------------------" << RESET << endl;
	return damage;
}
int menuFightEnemy(Enemy* enemy) {
	int damage = enemy->fight();
	loadingBar("Turno del enemigo...");
	cout << RED <<"--------------------------------" << RESET << endl;
	cout << RED << "TURNO DEL ENEMIGO" << RESET << endl;
	cout << RED << "--------------------------------" << RESET << endl;
	cout << ORANGE << "Daño recibido:___ " << RESET << damage << endl;
	cout << RED << "--------------------------------" << RESET << endl;
	return damage;
}
int menuDeadPlayer(Player* player, Enemy* enemy) {
	int dPlayer;
	int rerun = 0;
	dPlayer = player->deadPlayer(menuFightEnemy(enemy));
		if (dPlayer <= 0) {
			cout << RED << "--------------------------------" << RESET << endl;
			cout << RED << "HAS MUERTO" << RESET << endl;
			cout << RED << "--------------------------------" << RESET << endl;
			rerun = 1;
		}
		return rerun;
}
int menuDeadEnemy(Player* player, Enemy* enemy) {
	int dEnemy;
	int rerun = 0;
	dEnemy = enemy->deadEnemy(menuFightPlayer(player));
	if (dEnemy != 0) {
		player->upLevelEnemy(dEnemy);
		cout << GREEN <<"--------------------------------" << RESET << endl;
		cout << GREEN << "HAS MATADO AL ENEMIGO" << RESET << endl;
		cout << "--------------------------------" << endl;
		cout << "Experiencia:___ " << dEnemy << endl;
		rerun = 1;
	}
	return rerun;
}
void menuFightPrincipal(Player* player, Enemy* enemy) {
	cout << MAGENTA << "--------------------------------" << RESET << endl;
	cout << "PELEA" << endl;
	cout << MAGENTA << "--------------------------------" << RESET << endl;
		//Pelea
		int dPlayer,dEnemy;
		dEnemy = menuDeadEnemy(player, enemy);
		if ( dEnemy== 0) {
			dPlayer = menuDeadPlayer(player, enemy);
			//Vida
			if ( dPlayer== 0) {
				cout << MAGENTA << "================================" << RESET << endl;
				cout << RED <<"Vida del enemigo:_____" << RESET << enemy->getLife() << " hp" << endl;
				cout << LBLUE <<"Vida del jugador:_____" << RESET <<player->getLife() << " hp" << endl;
				cout << MAGENTA << "================================" << RESET << endl;
			}
		}
}

// Menú del juego
int Menu(Player* player, Three* three, Enemy* enemy) {
	int a;
	cout << YELLOW << "--------------------------------" << RESET << endl;
	cout << "    MENU PRINCIPAL" << endl;
	cout << YELLOW << "--------------------------------" << RESET <<  endl;
	cout << "1) Mirar personaje" << endl;
	cout << "2) Mirar Arbol" << endl;
	cout << "3) Mirar Enemigo" << endl;
	cout << "4) Talar Arbol" << endl;
	cout << "5) Pelear contra el enemigo" << endl;
	cout << "6) Cerrar juego" << endl;
	cout << YELLOW <<"--------------------------------" << RESET << endl;
	cout << "Selecciona una opcion: ";
	cin >> a;
	switch (a) {
	case 1:
		cout << BLUE << "--------------------------------" << RESET <<  endl;
		cout << LBLUE << "PERSONAJE" << RESET <<endl;
		cout << BLUE << "--------------------------------" << RESET <<  endl;
		cout << "Vida:_________" << player->getLife() << " hp" << endl;
		cout << "Nivel:________" << player->getLevel() << endl;
		cout << "Fuerza:_______" << player->getPower() << endl;
		cout << "Experiencia:__" << player->getExp() << endl;
		cout << "Kills:________" << player->getKill() << endl;
		cout << "Muertes:______" << player->getDead() << endl;
		PauseMenu();
		break;
	case 2:
		cout << GREEN << "--------------------------------" << RESET << endl;
		cout << LGREEN << "ARBOL" << RESET << endl;
		cout << GREEN << "--------------------------------" << RESET << endl;
		cout << "Vida:_________" << three->getLife() << " hp" << endl;
		cout << "Nivel:________" << three->getLevel() << endl;
		cout << "Experiencia:__" << three->getExp() << endl;
		PauseMenu();
		break;
	case 3:
		cout << RED << "--------------------------------" << RESET << endl;
		cout << RED << "ENEMIGO" << RESET << endl;
		cout << RED << "--------------------------------" << RESET << endl;
		cout << "Vida:_________" << enemy->getLife() << " hp" << endl;
		cout << "Nivel:________" << enemy->getLevel() << endl;
		cout << "Fuerza:_______" << enemy->getPower() << endl;
		cout << "Experiencia:__" << enemy->getExp() << endl;
		PauseMenu();
		break;
	case 4:
		player->upLevelThree();
		loadingBar("Cargando entorno...");
		cout << "Haz golpeado el arbol" << endl;
		cout << GREEN << "Vida Arbol:___" << RESET << three->getLife() << " hp" << endl;
		PauseMenu();
		break;
	case 5:
		menuFightPrincipal(player, enemy);
		PauseMenu();
		break;
	default:
		break;
	}
	return a;
}

int MenuRepeat(Player* player, Three* three, Enemy* enemy) {
	int repeat = Menu(player, three, enemy);
	int ret = 1;
	if (repeat > 6 || repeat < 1) {
		cout << "La opcion escogida no es valida" << endl;
		cout << "Vuelve a intentarlo" << endl;
		PauseMenu();
	}
	else {
		if (repeat == 6) {
			ret = 0;
		}
	}
	return ret;
}

int main() {
	Three* miarbol = new Three();
	Enemy* miEnemigo = new Enemy();
	Player jugador(miarbol, miEnemigo);
	int rerun = 1;
	while (rerun == 1) {
		rerun = MenuRepeat(&jugador, miarbol, miEnemigo);
	}
	system("cls");
	delete miarbol;
	delete miEnemigo;
	return 0;
}
