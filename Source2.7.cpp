#include <iostream>
#include <cstdlib>
#include <string>

class Enemy {
private:
	int life;
	int power;
	int exp;
	int level;
public:
	Enemy(int,int);
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
	
};
Enemy::Enemy(int life, int power) :life(life), power(power) { exp = 10; level = 1; }
Enemy::~Enemy() {
	std::cout << "El enemigo fue destruido" << std::endl;
}
//getters
int Enemy::getLife() { return life; }
int Enemy::getPower() { return power; }
int Enemy::getExp() { return exp;}
int Enemy::getLevel() { return level; }
//setters
void Enemy::setLife(int life) { this->life = life; }
void Enemy::setPower(int power) { this->power = power; }
void Enemy::setExp(int exp) { this->exp = exp; }
void Enemy::setLevel(int level) { this->level = level; }


class Three {
private:
	int life;
	int exp;
	int level;
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
int Three::getExp(){return exp;}
int Three::getLevel(){return level;}
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
	if (reduceLife(value) <=0) {
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
	Player(Three*,Enemy*);
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
	void hitEnemy();
	void takeDamage();
	int killEnemy();
};
Player::Player(Three* three, Enemy* enemy) {
	life = 10;
	level = 1;
	power = 1;
	exp = 0;
	kill = 0;
	dead = 0;
	myThree = three;
	myEnemy = enemy;
}
Player::~Player() {
	std::cout << "Player ha sido eliminado" << std::endl;
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
	int value=myThree->deadThree(-power);
	return value;
}
void Player::hitEnemy() {
	
}
void Player::takeDamage() {
	
}
int Player::killEnemy() {
	return 0;
}
//Menu
void PauseMenu(){
	system("pause");
	std::cout<<"\t"<<"Escribe cualquier letra"<<std::endl;
	system("cls");
}
int Menu(Player* player, Three* three) {
	int a;
	std::cout<<"Elige la opcion"<<std::endl;
	std::cout<<"1) Mirar personaje"<<std::endl;
	std::cout<<"2) Mirar Arbol"<<std::endl;
	std::cout<<"3) Talar Arbol"<<std::endl;
	std::cout<<"5) Cerrar juego"<<std::endl;
	std::cin>>a;
	switch(a){
	case 1:
		std::cout<<"--------------------------------"<<std::endl;
		std::cout<<"PERSONAJE"<<std::endl;
		std::cout<<"--------------------------------"<<std::endl;
		std::cout<<"Vida:_________"<<player->getLife()<<" hp"<<std::endl;
		std::cout<<"Nivel:________"<<player->getLevel()<<std::endl;
		std::cout<<"Experiencia:__"<<player->getExp()<<std::endl;
		std::cout<<"Kills:________"<<player->getKill()<<std::endl;
		std::cout<<"Muertes:______"<<player->getDead()<<std::endl;
		PauseMenu();
		break;
	case 2:
		std::cout<<"--------------------------------"<<std::endl;
		std::cout<<"ARBOL"<<std::endl;
		std::cout<<"--------------------------------"<<std::endl;
		std::cout<<"Vida:_________"<<three->getLife()<<" hp"<<std::endl;
		std::cout<<"Nivel:________"<<three->getLevel()<<std::endl;
		std::cout<<"Experiencia:__"<<three->getExp()<<std::endl;
		PauseMenu();
		break;
	case 3:
		player->upLevelThree();
		std::cout<<"Haz golpeado el arbol"<<std::endl;
		std::cout<<"Vida Arbol:___"<<three->getLife()<<" hp"<<std::endl;
		PauseMenu();
		break;
	default:
		break;
	}
	return a;
}
int MenuRepeat(Player* player, Three* three){
	int repeat=Menu(player,three);
	int ret;
	if (repeat>5&&repeat<1){
		std::cout<<"La opcion escogida no hace parte de ninguna opcion"<<std::endl;
		std::cout<<"Vuenve a intentarlo"<<std::endl;
		PauseMenu();
		ret=1;
	}else {
		if (repeat==5){
			ret=0;
		}else{
			ret=1;
		}
	}
	return ret;
}
int main() {
	Three* miarbol=new Three();
	Enemy* miEnemigo = new Enemy(20,10);
	Player jugador(miarbol,miEnemigo);
	int rerun = 1;
	while (rerun==1) {
		rerun=MenuRepeat(&jugador,miarbol);
	}
	
	return 0;
}
