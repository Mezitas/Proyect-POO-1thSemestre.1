#include <iostream>
#include <cstdlib>
#include <string>

class Enemy {
private:
	int life;
	int power;
	int exp;
	int level;
	//methods
	int reduceLife(int);
	void upLevel();
public:
	Enemy();
	~Enemy();
	//getters
	int getLife();
	int getPower();
	int getExp();
	int getLevel();
	//Setters
	void setLife(int);
	void setPower(int);
	void setExp(int);
	void setLevel(int);
	//others
	int deadEnemy(int);
	void KillEnemy(int);
};
Enemy::Enemy() { 
	life = 20;
	power = 3;
	exp = 10; 
	level = 1; 
}
Enemy::~Enemy() {
	std::cout << "El enemigo fue destruido" << std::endl;
}
//getters
int Enemy::getLife() { return life; }
int Enemy::getPower() { return power; }
int Enemy::getExp() { return exp; }
int Enemy::getLevel() { return level; }
//setters
void Enemy::setLife(int life) { this->life = life; }
void Enemy::setPower(int power) { this->power = power; }
void Enemy::setExp(int exp) { this->exp = exp; }
void Enemy::setLevel(int level) { this->level = level; }
//others 
int Enemy::reduceLife(int power) {
	life += power;
	return life;
}
void Enemy::upLevel() {
	level++;
	life = 20 + (5 * level);
	exp = 10 + (5 * level);
	power = 3 + (5 * level);
}
int Enemy::deadEnemy(int power){
	int devolution = 0;
	if (reduceLife(power) < 0) {
		upLevel();
		devolution= exp;
	}
	return devolution;
}
void Enemy::KillEnemy(int reduceLife) {
	if (reduceLife <= 0) {
		if (level == 1) {
			life = 20;
			exp = 10;
			power = 3;
		}
		else {
			life = 20 + (5 * level);
			exp = 10 + (5 * level);
			power = 3 + (5 * level);
		}
	}
}

class Three {
private:
	int life;
	int exp;
	int level;
	//methods
	int reduceLife(int);
	void upLevel();
public:
	Three();
	~Three();
	//Getters
	int getLife();
	int getExp();
	int getLevel();
	//setters
	void setLife(int);
	//others
	int deadThree(int);
};
Three::Three() {
	life = 10;
	exp = 5;
	level = 1;
}
Three::~Three() {
	std::cout << "El arbol fue destruido" << std::endl;
}
//getters
int Three::getLife() { return life; }
int Three::getExp() { return exp; }
int Three::getLevel() { return level; }
//setters
void Three::setLife(int life) { this->life = life; }
//others
int Three::reduceLife(int value) {
	life += value;
	return life;
}
void Three::upLevel() {
	level++;
	life = 10 + (2 * level);
	exp = 5 + (2 * level);
}
int Three::deadThree(int value) {
	int devolution = 0;
	if (reduceLife(value) <= 0) {
		devolution = exp;
		upLevel();
	}
	return devolution;
}

class Player {
private:
	int life;
	int power;
	int exp;
	int level;
	int kill;
	int dead;
	Enemy* myEnemy;
	Three* myThree;
	//methods private
	void changeProperties();
public:
	Player(Three*, Enemy*);
	~Player();
	//Getters
	int getLife();
	int getPower();
	int getExp();
	int getLevel();
	int getKill();
	int getDead();
	//Setters
	void setLife(int);
	void setPower(int);
	void setExp(int);
	void setLevel(int);
	void setKill(int);
	void setDead(int);
	//Others
	void upLevel();
	void upLevelThree();
	int hitThree();
	int fight();
	int hitEnemy();
	int takeDamage();
	void upLevelEnemy();
	int deadPlayer();
};
Player::Player(Three* three, Enemy* enemy) {
	life = 10;
	level = 1;
	power = 2;
	exp = 0;
	kill = 0;
	dead = 0;
	myThree = three;
	myEnemy = enemy;
}
Player::~Player() {
	std::cout << "El jugador ha sido eliminado" << std::endl;
}
//Getters
int Player::getLife() { return life; }
int Player::getPower() { return power; }
int Player::getExp() { return exp; }
int Player::getLevel() { return level; }
int Player::getKill() { return kill; }
int Player::getDead() { return dead; }
//Setters
void Player::setLife(int value) { life = value; }
void Player::setPower(int value) { power = value; }
void Player::setExp(int value) { exp = value; }
void Player::setLevel(int value) { level = value; }
void Player::setKill(int value) { kill = value; }
void Player::setDead(int value) { dead = value; }
//others
void Player::changeProperties() {
	life = 10 + (level * 2);
	power = 2 + level;
	exp = 0;
}
void Player::upLevel() {
	if (exp >= level * 5) {
		level++;
		changeProperties();
	}

}
void Player::upLevelThree() {
	int newValue = hitThree();
	if (newValue > 0) {
		exp += newValue;
		upLevel();
	}
}

int Player::hitThree() {
	int value = myThree->deadThree(-power);
	return value;
}

int Player::hitEnemy() {
	int value = myEnemy->deadEnemy(-power);
	return value;
}
int Player::takeDamage() {
	 int damage = myEnemy->getPower();
	 return damage;
}
int Player::deadPlayer() {
	int value=takeDamage();
	int lifeActual = life -= value;
	if (lifeActual<= 0) {
		value = 0;
		myEnemy->KillEnemy(lifeActual);
		life = 10;
		power = 2;
		exp = 0;
		level = 1;
		dead++;
		
	}
	return -value;
}
void Player::upLevelEnemy() {
	int experience = hitEnemy();
	if (experience > 0) {
		exp += experience;
		kill++;
		upLevel();
	}
}
int Player::fight() {
	int devolution = power;
	int punch = rand() % 11;
	if (punch%2==0) {
		upLevelEnemy();
	}
	else {
		devolution = deadPlayer();
	}
	return devolution;
}

//Menu
void PauseMenu() {
	system("pause");
	system("cls");
}
void menuFight(Player* player,Enemy* enemy) {
	int result=player->fight();
	std::cout << "--------------------------------" << std::endl;
	std::cout << "PELEA" << std::endl;
	std::cout << "--------------------------------" << std::endl;
	if(result==0){
		std::cout << "Haz Muerto. . .";
		PauseMenu();
	}
	else {
		if (result > 0) {

			std::cout << "Haz hecho:_____" << player->getPower() << " damage" << std::endl;
		}
		else {
			std::cout << "Haz recibido:__" << enemy->getPower() << " damage" << std::endl;
		}
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Vida del enemigo:_____" << enemy->getLife() << " hp" << std::endl;
		std::cout << "Vida del jugador:_____" << player->getLife() << " hp" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		PauseMenu();
	}
	
}
int Menu(Player* player, Three* three,Enemy* enemy) {
	int a;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "ELIGE UNA OPCION" << std::endl;
	std::cout << "--------------------------------" << std::endl;
	std::cout << "1) Mirar personaje" << std::endl;
	std::cout << "2) Mirar Arbol" << std::endl;
	std::cout << "3) Mirar Enemigo" << std::endl;
	std::cout << "4) Talar Arbol" << std::endl;
	std::cout << "5) Pelear contra el enemigo" << std::endl;
	std::cout << "6) Cerrar juego" << std::endl;
	std::cin >> a;
	switch (a) {
	case 1:
		std::cout << "--------------------------------" << std::endl;
		std::cout << "PERSONAJE" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Vida:_________" << player->getLife() << " hp" << std::endl;
		std::cout << "Nivel:________" << player->getLevel() << std::endl;
		std::cout << "Fuerza:_______" << player->getPower() << std::endl;
		std::cout << "Experiencia:__" << player->getExp() << std::endl;
		std::cout << "Kills:________" << player->getKill() << std::endl;
		std::cout << "Muertes:______" << player->getDead() << std::endl;
		PauseMenu();
		break;
	case 2:
		std::cout << "--------------------------------" << std::endl;
		std::cout << "ARBOL" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Vida:_________" << three->getLife() << " hp" << std::endl;
		std::cout << "Nivel:________" << three->getLevel() << std::endl;
		std::cout << "Experiencia:__" << three->getExp() << std::endl;
		PauseMenu();
		break;
	case 3:
		std::cout << "--------------------------------" << std::endl;
		std::cout << "ENEMIGO" << std::endl;
		std::cout << "--------------------------------" << std::endl;
		std::cout << "Vida:_________" << enemy->getLife() << " hp" << std::endl;
		std::cout << "Nivel:________" << enemy->getLevel() << std::endl;
		std::cout << "Fuerza:_______" << enemy->getPower() << std::endl;
		std::cout << "Experiencia:__" << enemy->getExp() << std::endl;
		PauseMenu();
		break;
	
	case 4:
		player->upLevelThree();
		std::cout << "Haz golpeado el arbol" << std::endl;
		std::cout << "Vida Arbol:___" << three->getLife() << " hp" << std::endl;
		PauseMenu();
		break;
	case 5:
		menuFight(player,enemy);
		break;
	default:
		break;
	}
	return a;
}
int MenuRepeat(Player* player, Three* three,Enemy* enemy) {
	int repeat = Menu(player, three,enemy);
	int ret=1;
	if (repeat > 6 || repeat < 1) {
		std::cout << "La opcion escogida no es valida" << std::endl;
		std::cout << "Vuelve a intentarlo" << std::endl;
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
		rerun = MenuRepeat(&jugador, miarbol,miEnemigo);
	}
	system("cls");
	delete(miarbol);
	delete(miEnemigo);
	return 0;
}