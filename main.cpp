#include <iostream>
#include <cstdlib>
#include <string>
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
int menuFightPlayer(Player* player) {
	int damage = player->fight();
	cout << "TURNO DEL JUGADOR" << endl;
	cout << "--------------------------------" << endl;
	cout << "Daño hecho:___ " << damage << endl;
	return damage;
}
int menuFightEnemy(Enemy* enemy) {
	int damage = enemy->fight();
	cout << "--------------------------------" << endl;
	cout << "TURNO DEL ENEMIGO" << endl;
	cout << "--------------------------------" << endl;
	cout << "Daño recibido:___ " << damage << endl;
	return damage;
}
int menuDeadPlayer(Player* player, Enemy* enemy) {
	int dPlayer;
	int rerun = 0;
	dPlayer = player->deadPlayer(menuFightEnemy(enemy));
		if (dPlayer <= 0) {
			cout << "--------------------------------" << endl;
			cout << "HAZ MUERTO" << endl;
			cout << "--------------------------------" << endl;
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
		cout << "--------------------------------" << endl;
		cout << "HAZ MATADO AL ENEMIGO" << endl;
		cout << "--------------------------------" << endl;
		cout << "Experiencia:___ " << dEnemy << endl;
		rerun = 1;
	}
	return rerun;
}
void menuFightPrincipal(Player* player, Enemy* enemy) {
		cout << "--------------------------------" << endl;
		cout << "PELEA" << endl;
		cout << "--------------------------------" << endl;
		//Pelea
		int dPlayer,dEnemy;
		dEnemy = menuDeadEnemy(player, enemy);
		if ( dEnemy== 0) {
			dPlayer = menuDeadPlayer(player, enemy);
			//Vida
			if ( dPlayer== 0) {
				cout << "--------------------------------" << endl;
				cout << "--------------------------------" << endl;
				cout << "Vida del jugador:____ " << player->getLife() << "hp" << endl;
				cout << "Vida del enemigo:____ " << enemy->getLife() << "hp" << endl;
				cout << "--------------------------------" << endl;
				cout << "--------------------------------" << endl;
			}

		}
		
}

// Menú del juego
int Menu(Player* player, Three* three, Enemy* enemy) {
	int a;
	cout << "--------------------------------" << endl;
	cout << "ELIGE UNA OPCION" << endl;
	cout << "--------------------------------" << endl;
	cout << "1) Mirar personaje" << endl;
	cout << "2) Mirar Arbol" << endl;
	cout << "3) Mirar Enemigo" << endl;
	cout << "4) Talar Arbol" << endl;
	cout << "5) Pelear contra el enemigo" << endl;
	cout << "6) Cerrar juego" << endl;
	std::cin >> a;
	switch (a) {
	case 1:
		cout << "--------------------------------" << endl;
		cout << "PERSONAJE" << endl;
		cout << "--------------------------------" << endl;
		cout << "Vida:_________" << player->getLife() << " hp" << endl;
		cout << "Nivel:________" << player->getLevel() << endl;
		cout << "Fuerza:_______" << player->getPower() << endl;
		cout << "Experiencia:__" << player->getExp() << endl;
		cout << "Kills:________" << player->getKill() << endl;
		cout << "Muertes:______" << player->getDead() << endl;
		PauseMenu();
		break;
	case 2:
		cout << "--------------------------------" << endl;
		cout << "ARBOL" << endl;
		cout << "--------------------------------" << endl;
		cout << "Vida:_________" << three->getLife() << " hp" << endl;
		cout << "Nivel:________" << three->getLevel() << endl;
		cout << "Experiencia:__" << three->getExp() << endl;
		PauseMenu();
		break;
	case 3:
		cout << "--------------------------------" << endl;
		cout << "ENEMIGO" << endl;
		cout << "--------------------------------" << endl;
		cout << "Vida:_________" << enemy->getLife() << " hp" << endl;
		cout << "Nivel:________" << enemy->getLevel() << endl;
		cout << "Fuerza:_______" << enemy->getPower() << endl;
		cout << "Experiencia:__" << enemy->getExp() << endl;
		PauseMenu();
		break;
	case 4:
		player->upLevelThree();
		cout << "Haz golpeado el arbol" << endl;
		cout << "Vida Arbol:___" << three->getLife() << " hp" << endl;
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